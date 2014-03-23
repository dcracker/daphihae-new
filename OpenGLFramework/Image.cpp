
#include "stdafx.h"

#include "Image.h"
#include "IFile.h"
#include "png.h"

#include "logger.h"
#define LOG_TAG "Image"

Image::Image( int width, int height, GLint colorFormat, BYTE* byteBuffer )
	: cWidth( width )
	, cHeight( height )
	, cColorFormat( colorFormat )
	, cImageData( byteBuffer )
{
}

Image::~Image() {
	delete const_cast<BYTE*>(cImageData);
}


#define RETURN_ERROR(...) \
	LOG_ERROR( __VA_ARGS__ );\
	return NULL

// ref : http://stackoverflow.com/questions/11296644/loading-png-textures-to-opengl-with-libpng-only
// ref : book - Android NDK Beginner's Guide
static void png_read_callback( png_structp png, png_bytep data, png_size_t size );

Image* Image::LoadPNG( IFile* file ) {
	png_byte header[8];
	if ( file->ReadByte( header, sizeof(header) ) == false ) {
		RETURN_ERROR( "failed to read png header from %s", file->GetFileName( ) );
	}

	if ( png_sig_cmp(header, 0, 8) != 0 ) {
		RETURN_ERROR( "%s is not png format!", file->GetFileName( ) );
	}

	png_structp png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	if ( png_ptr == NULL ) {
		RETURN_ERROR( "png_create_read_struct returned 0" );
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if ( info_ptr == NULL ) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		RETURN_ERROR( "png_create_info_struct returned 0" );
	}

	// create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if ( end_info == NULL )
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		RETURN_ERROR( "error: png_create_info_struct returned 0" );
	}

	// init png reading
	png_set_read_fn( png_ptr, file, png_read_callback );

	// the code in this if statement gets called if libpng encounters an error
	if ( setjmp( png_jmpbuf( png_ptr ) ) ) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		RETURN_ERROR( "error from libpng" );
	}

	// let libpng know you already read the first 8 bytes
	png_set_sig_bytes( png_ptr, 8 );

	// read all the info up to the image data
	png_read_info( png_ptr, info_ptr );

	// variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 width, height;

	// get info about png
	png_get_IHDR( png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL );

	bool hasAlpha = false;
	if ( png_get_valid( png_ptr, info_ptr, PNG_INFO_tRNS ) ) {
		png_set_tRNS_to_alpha( png_ptr );
		hasAlpha = true;
	}
	// Expands PNG with less than 8bits per channel to 8bits.
	if ( bit_depth < 8 ) {
		png_set_packing ( png_ptr );
	// Shrinks PNG with 16bits per color channel down to 8bits.
	}
	else if ( bit_depth == 16 ) {
		png_set_strip_16( png_ptr );
	}
	// Indicates that image needs conversion to RGBA if needed.
	GLint format;
	switch ( color_type ) {
	case PNG_COLOR_TYPE_PALETTE:
		png_set_palette_to_rgb( png_ptr );
		format = hasAlpha ? GL_RGBA : GL_RGB;
		break;
	case PNG_COLOR_TYPE_RGB:
		format = hasAlpha ? GL_RGBA : GL_RGB;
		break;
	case PNG_COLOR_TYPE_RGBA:
		format = GL_RGBA;
		break;
	case PNG_COLOR_TYPE_GRAY:
		png_set_expand_gray_1_2_4_to_8( png_ptr );
		format = hasAlpha ? GL_LUMINANCE_ALPHA:GL_LUMINANCE;
		break;
	case PNG_COLOR_TYPE_GA:
		png_set_expand_gray_1_2_4_to_8( png_ptr );
		format = GL_LUMINANCE_ALPHA;
		break;
    default:
        format = 0;
        break;
	}

	// Update the png info struct.
	png_read_update_info( png_ptr, info_ptr );

	// Row size in bytes.
	int rowbytes = png_get_rowbytes( png_ptr, info_ptr );

	// glTexImage2d requires rows to be 4-byte aligned
	rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block, to be given to opengl
	png_byte* image_data;
	image_data = new png_byte[rowbytes * height * sizeof(png_byte) + 15];
	if (image_data == NULL) {
		delete[] image_data;
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		RETURN_ERROR( "could not allocate memory for PNG image data" );
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep* row_pointers = new png_bytep[height * sizeof(png_bytep)];
	if (row_pointers == NULL) {
		delete[] image_data;
		delete[] row_pointers;
		png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		RETURN_ERROR( "could not allocate memory for PNG row pointers" );
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for ( unsigned int i = 0; i < height; i++ ) {
		row_pointers[height - 1 - i] = image_data + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image( png_ptr, row_pointers );

	png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );

	return new Image( width, height, format, image_data );
}

static void png_read_callback(png_structp png, png_bytep data, png_size_t size) {
	IFile* file = (IFile*)png_get_io_ptr( png );
	if ( file->ReadByte( data, size ) == false ) {
		LOG_ERROR( "Error while reading PNG file" );
	}
}
