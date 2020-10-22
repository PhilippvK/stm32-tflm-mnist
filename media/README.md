# Media

If touchscreen input is not deterministic/reliable enough for the 'MNIST' example, optionally real samples from the dataset can be fed into the neural network. The following sections should explain to to make use of this feature.

## Requirements

- (Empty) SD-Card (f.e. 2GB), formatted with FATFS
- Software:
  - `wget`, `gzip` (should be installed by default on any UNIX system) (TODO)
  - `python3` (with `pip` and modules listed in [`requirements.txt`](TODO))
```
python3 -m pip install -r requirements.txt
```

## Configure CMake

0. Check if your board is compatible. See: [Boards](TODO)

1. Edit `CMakeLists.txt` an make sure, that the `FAKE_TOUCH` option is enabled

```
### Configure 'mnist' Example ###
SET(FAKE_TOUCH ON) # Use SD Card instead of Microphone
...
```

2. Recompile and flash the program
```
cd build
cmake ..
make flash
```

## Generate Files

**Hint:** You can skip this step you just using the contents of the `sd_card.zip` archive which can be downloaded [here](https://raw.githubusercontent.com/PhilippvK/stm32-tflm-demos/master/media/sd_card.zip).

### Why can't I just use the original dataset

STM's Board Support Package Driver does only support to draw 16 bit RGB(565) encoded BMP-Files on the LCD, the samples in the [original dataset](TODO) are encoded with 8-bit grayscale values.

**Warning:** The Neural Network is trained with images of white numbers from 0-9 on a black background. Often the inverted version of this is shown which can result in wrong behavior!

### Steps

1. Download and extract the dataset consisting of images and labels from [http://yann.lecun.com/exdb/mnist/](http://yann.lecun.com/exdb/mnist/)

```
mkdir /tmp/mnist_temp
cd /tmp/mnist_temp
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
gzip -d train-images-idx3-ubyte.gz
gzip -d train-labels-idx1-ubyte.gz
cd -
```

**Warning:** While the file sizes in the dataset are quite small, the total number of files is very large, which makes some systems crash when opening the directory.

2. Now the binary samples can be exported as BMP-Files. The export and format conversion can be done running the following command which may run for several minutes because of the large number of files:

```
mkdir /tmp/mnist_dataset
python3 convert_mnist_dataset.py /tmp/mnist_temp/train-images-idx3-ubyte /tmp/mnist_temp/train-labels-idx1-ubyte /tmp/mnist_dataset
```

*Short Manual:* `Usage: ./convert_mnist_files.py [IMAGES_DATA] [LABELS_DATA] [OUTPUT_DIR]`

3. After exporting and converting the image files, instead manually picking files to use, the script `gen_mnist_files.sh` can select a random set of samples for you using the following line of code:
 
```
mkdir -p output/mnist
rm -f output/mnist/* # Remove old files
./gen_mnist_files.sh /tmp/mnist_dataset ./output/mnist 10
```

*Short Manual:* `Usage: ./gen_mnist_files.sh [DATASET_DIR] [OUTPUT_DIR] [COUNT]`

## Setup SD-Card

Copy the `mnist` directory either from the `media/output/` directory or from where you extracted the contents of [`sd_card.zip`](https://raw.githubusercontent.com/PhilippvK/stm32-tflm-demos/master/media/sd_card.zip) to directory to the root directory of the SD card.


## Run the Program

Up to 16 `*.bmp` files found in the `mnist` directory on the SD-Card displayed at the center of the screen and feed into the Neural Network. The classification probabilities are printed for a short moment before the next image of the SD-Card is chosen automatically.

The name of the current file is displayed on the touchscreen. Additionally all files found when reading the directory are printed on UART before the network starts.

To make debugging more easy, an ASCII-like representation of the images can be printed to UART as well. (See example in [`USAGE.md`](TODO))
