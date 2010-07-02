/* This file is (c) 2008-2010 Konstantin Isakov <ikm@users.berlios.de>
 * Part of GoldenDict. Licensed under GPLv3 or later, see the LICENSE file */

#ifndef __ZIPFILE_HH_INCLUDED__
#define __ZIPFILE_HH_INCLUDED__

#include <QFile>

/// Support for zip files in GoldenDict. Note that the implementation is
/// strictly tailored to GoldenDict needs only.
namespace ZipFile {

enum CompressionMethod
{
  Uncompressed,
  Deflated,
  Unsupported
};

/// Entry from central dir
struct CentralDirEntry
{
  QByteArray fileName;

  quint32 localHeaderOffset, compressedSize, uncompressedSize;
  CompressionMethod compressionMethod;
};

/// Represents contents of the local file header -- that what CentralDirEntry::
/// localHeaderOffset points at.
struct LocalFileHeader
{
  QByteArray fileName;

  quint32 compressedSize, uncompressedSize;
  CompressionMethod compressionMethod;
};

/// Finds the central directory in the given file and positions it at its
/// beginning. Returns true if the file is positioned, false otherwise (not a
/// zip file or other error).
/// Once the file is positioned, entries may be read by constructing Entry
/// objects.
bool positionAtCentralDir( QFile & );

/// Reads entry from the zip at its current offset. The file gets advanced
/// by the size of entry, so it points to the next entry.
/// Returns true on success, false otherwise.
bool readNextEntry( QFile &, CentralDirEntry & );

/// Reads loca file header from the zip at its current offset. The file gets
/// advanced by the size of entry and starts pointing to file data.
/// Returns true on success, false otherwise.
bool readLocalHeader( QFile &, LocalFileHeader & );

}

#endif