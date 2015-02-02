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
   Filesystem.hpp
   Path.hpp
   FileInfo.hpp
   IFilesystem.hpp

   io/File.hpp
   io/IFileReader.hpp
   io/UnbufferedFileReader.hpp

   compression/ZipArchive.hpp

   exceptions/FileNotFoundException.hpp
   exceptions/InvalidFileTypeException.hpp
   exceptions/StreamErrorException.hpp

   internal/UnixAbstractionLayer.hpp
   internal/WindowsAbstraction.hpp
)


add_library(gc_filesystem OBJECT ${gc_filesystem_src} ${gc_filesystem_headers})