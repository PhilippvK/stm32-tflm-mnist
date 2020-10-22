#!/usr/bin/python3

import struct
import numpy as np
from PIL import Image
import sys
import os

if len(sys.argv) != 4:
    print("Invalid number or arguments! Aborting...")
    print("Usage: ./convert_mnist_files.py [IMAGES_DATA] [LABELS_DATA] [OUTPUT_DIR]")
    exit(1)
else:
    images_filename = sys.argv[1]
    if not os.path.exists(images_filename):
        print("File '{}' does ot exist! Aborting...".format(images_filename))
        exit(1)
    labels_filename = sys.argv[2]
    if not os.path.exists(labels_filename):
        print("File '{}' does ot exist! Aborting...".format(labels_filename))
        exit(1)
    dataset_dir = sys.argv[3]
    if not os.path.exists(dataset_dir):
        print("Directory '{}' does ot exist! Aborting...".format(dataset_dir))
        exit(1)

# TODO: ADD LINK
# DISCLAIMER:
#
# A majority of the code in this script is taken from:
# https://www.python-forum.de/viewtopic.php?t=5834
#
# I modified the script to generate 16bit RGB from 8 bit
# Grayscale instead of 24 bit RGB
#

class BMPError(Exception):
    """Error for problems with BMP file."""
    pass


class BMP(object):
    """BMP image.
    
    A `BMP` object can load and save very simple BMP images.  It is very
    restrictive; just uncompressed 24 bits per pixel BMPs can be loaded.
    
    HEADER_FMT : `str`
        Format in `struct` notation of the beginning of the BMP header
        structure including all relevant fields.
    HEADER_SIZE : `int`
        Size of the header structure described by `HEADER_FMT` in bytes.
    signature : `str` of length two
        BMP signature.  Must be ``BM``.
    file_size : `int`
        Size of the complete image file including header(s) and image data.
    data_offset : `int`
        Offset into the file where the image data starts.
    info_size : `int`
        Size of the info header structure.  It's 40 bytes for most BMPs.
    width, height : `int`
        Dimensions of the image in pixels.
    planes : `int`
        No idea!?  Has to be 1.
    bit_count : `int`
        Number of bits per pixel.
    compression : `int`
        Compression method.  0 means no compression.
    data_size : `int`
        Size of the (compressed) data in bytes.  If no compression is used
        this field may be set to 0.
    remaining_header : `str`
        Data between first part of the header and the image data.
    bytes_per_row : `int`
        Number of bytes per pixel row in the image data.
    data : `str`
        The image data.
    """
    HEADER_FMT = '< 2s i 4x i iii hh ii'
    HEADER_SIZE = struct.calcsize(HEADER_FMT)
    
    def __init__(self, fileobj):
        """Create a `BMP` object from the content of `fileobj`.
        
        Raises `BMPError` if the BMP in `fileobj` is not an uncompressed
        24 bits per pixel BMP.
        """
        (self.signature,
         self.file_size,
         self.data_offset,
         self.info_size,
         self.width,
         self.height,
         self.planes,
         self.bit_count,
         self.compression,
         self.data_size
        ) = struct.unpack(self.HEADER_FMT, fileobj.read(self.HEADER_SIZE))
        
        if self.signature.decode("utf-8") != 'BM':
            raise BMPError('not a BMP')
        if self.planes != 1:
            raise BMPError('image has more than one plane')
        if self.bit_count != 24:
            raise BMPError('not a 24 bpp image')
        if self.compression != 0:
            raise BMPError('compressed image')
        
        self.remaining_header = fileobj.read(  self.data_offset
                                             - self.HEADER_SIZE)
        self.data = fileobj.read()
        
        self.bytes_per_row = None
        self._calculate_bytes_per_row()

    def _calculate_bytes_per_row(self):
        """Calculate the bytes per row.
        
        Row data in BMP images is padded to 32 bit boundaries.
        """
        self.bytes_per_row = ((self.width * self.bit_count - 1) // 32) * 4 + 4
    
    def iter_rows(self):
        """Iterate over the data of the rows."""
        for i in range(self.height):
            offset = i * self.bytes_per_row
            yield self.data[offset:offset+self.bytes_per_row]
    
    def _iter_pixels(self, rowdata):
        """Iterate over RGB values in `rowdata`.
        
        Returns an iterator over tuples with red, green and blue values as
        `int`\s between 0 and 255.
        """
        for i in range(self.width):
            yield list(rowdata[i*3:i*3+3])
    
    def convert_to_16_bit(self):
        """Convert image to 16 bits per pixel."""
        assert self.bit_count in (24, 16)
        if self.bit_count == 16:
            return
        # 
        # Convert image data.
        # 
        new_data = list()
        for rowdata in self.iter_rows():
            new_row = list()
            for red, green, blue in self._iter_pixels(rowdata):
                new_row.append(  ((blue >> 3) << 11)
                               + ((green >> 2) << 5)
                               +  (red >> 3))
            new_data.append(new_row)
        # 
        # Adjust header information and pack image data.
        # 
        self.bit_count = 16
        self.data_size = 0
        self._calculate_bytes_per_row()
        row_fmt = (  'H' * self.width
                   + 'x' * (self.bytes_per_row // 2 - self.width))
        self.data = b''.join(struct.pack(row_fmt, *(row)) for row in new_data)
        self.file_size = self.data_offset + len(self.data)
    
    @classmethod
    def load(cls, filename):
        """Load a BMP file and return a `BMP` object."""
        bmp_file = open(filename, 'rb')
        result = cls(bmp_file)
        bmp_file.close()
        return result
    
    def save(self, filename):
        """Save `BMP` object to a file."""
        bmp_file = open(filename, 'wb')
        header = struct.pack(self.HEADER_FMT,
                             self.signature,
                             self.file_size,
                             self.data_offset,
                             self.info_size,
                             self.width,
                             self.height,
                             self.planes,
                             self.bit_count,
                             self.compression,
                             self.data_size)
        bmp_file.write(header)
        bmp_file.write(self.remaining_header)
        bmp_file.write(self.data)
        bmp_file.close()

def main():
    images_file = open(images_filename, 'rb')
    labels_file = open(labels_filename, 'rb')
    images_buf = images_file.read()
    labels_buf = labels_file.read()
    
    images_index = 0
    labels_index = 0

    # read 4 unsigned int with big-endian format
    images_magic, images_len, images_rows, images_cols = struct.unpack_from('>IIII', images_buf, images_index)
    images_index += struct.calcsize('>IIII')  # move the cursor

    labels_magic, labels_len = struct.unpack_from('>II', labels_buf, labels_index)
    labels_index += struct.calcsize('>II')  # move the cursor
    
    # Count the number of available samples per digit
    counts = [0 for _ in range(0, 10)]
    
    for image in range(0, images_len): # TODO

        # the image is 28*28=784 unsigned chars
        im = struct.unpack_from('>784B', images_buf, images_index)
        images_index += struct.calcsize('>784B')  # move the cursor

        label = struct.unpack_from('>1B', labels_buf, labels_index)[0]
        labels_index += struct.calcsize('>1B')  # move the cursor
    
        # create a np array to save the image
        im = np.array(im, dtype='uint8')
        im = im.reshape(28, 28)
    
        # Update counts
        counts[label] += 1

        # Convert Image to RGB
        im = Image.fromarray(im)
        im = im.convert("RGB")

        filename = "{}/train_{}_{}.bmp".format(dataset_dir, label, counts[label]) 
        print("Exporting {}...".format(filename))
        im.save(filename, "bmp")
        bmp = BMP.load(filename) 
        print("Converting {}...".format(filename))
        bmp.convert_to_16_bit()
        print("Saving {}...".format(filename))
        bmp.save(filename)

if __name__ == "__main__":
    main()
