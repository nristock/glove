set(gc_filesystem_src
   Path.cc

   internal/UnixAbstractionLayer.cc

   io/File.cc
   io/UnbufferedFileReader.cc

   compression/ZipArchive.cc
   compression/ZipEntry.cc
   compression/ZipEntryBuffer.cc
   compression/ZipFilesystem.cc

   exceptions/FileNotFoundException.cc
   exceptions/InvalidFileTypeException.cc
   exceptions/StreamErrorException.cc
   exceptions/FileInfoQueryException.cc
)

set(gc_filesystem_headers
   compression/Compression.hpp

   io/IFileReader.hpp

   FileInfo.hpp
   Filesystem.hpp
   IFilesystem.hpp
)


add_library(gc_filesystem OBJECT ${gc_filesystem_src} ${gc_filesystem_headers})