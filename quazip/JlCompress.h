#ifndef JLCOMPRESSFOLDER_H_
#define JLCOMPRESSFOLDER_H_

/*
Copyright (C) 2010 Roberto Pompermaier
Copyright (C) 2005-2016 Sergey A. Tachenov

This file is part of QuaZIP.

QuaZIP is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

QuaZIP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with QuaZIP.  If not, see <http://www.gnu.org/licenses/>.

See COPYING file for the full LGPL text.

Original ZIP package is copyrighted by Gilles Vollant and contributors,
see quazip/(un)zip.h files for details. Basically it's the zlib license.
*/

#include "quazip.h"
#include "quazipfile.h"
#include "quazipfileinfo.h"
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <functional>

/// Utility class for typical operations.
/**
  This class contains a number of useful static functions to perform
  simple operations, such as mass ZIP packing or extraction.
  */
class QUAZIP_EXPORT JlCompress {
public:
	using FilterFunction = std::function<bool(const QString &)>;
public:
    static bool copyData(QIODevice &inFile, QIODevice &outFile);
    static bool removeFile(QStringList listFile);
public:
    /// Compress a single file.
    /**
      \param fileCompressed The name of the archive.
      \param file The file to compress.
      \return true if success, false otherwise.
      */
    static bool compressFile(QString fileCompressed, QString file);
    static bool compressFile(QuaZip* zip, QString fileName, QString fileDest);
    /// Compress a list of files.
    /**
      \param fileCompressed The name of the archive.
      \param files The file list to compress.
      \return true if success, false otherwise.
      */
    static bool compressFiles(QString fileCompressed, QStringList files);
    /// Compress a whole directory.
    /**
      Does not compress hidden files. See compressDir(QString, QString, bool, QDir::Filters).

      \param fileCompressed The name of the archive.
      \param dir The directory to compress.
      \param recursive Whether to pack the subdirectories as well, or
      just regular files.
      \return true if success, false otherwise.
      */
    //static bool compressDir(QString fileCompressed, QString dir = QString(), bool recursive = true);
    /**
     * @brief Compress a whole directory.
     *
     * Unless filters are specified explicitly, packs
     * only regular non-hidden files (and subdirs, if @c recursive is true).
     * If filters are specified, they are OR-combined with
     * <tt>%QDir::AllDirs|%QDir::NoDotAndDotDot</tt> when searching for dirs
     * and with <tt>QDir::Files</tt> when searching for files.
     *
     * @param fileCompressed path to the resulting archive
     * @param dir path to the directory being compressed
     * @param recursive if true, then the subdirectories are packed as well
     * @param filters what to pack, filters are applied both when searching
     * for subdirs (if packing recursively) and when looking for files to pack
     * @return true on success, false otherwise
     */
    //static bool compressDir(QString fileCompressed, QString dir, bool recursive, QDir::Filters filters);

    // prefix is added to all the compressed files paths
    static bool compressDir(QString fileCompressed, QString dir, QString prefix = QString(), const FilterFunction filter = nullptr);
    /// Compress a subdirectory.
    /**
      \param parentZip Opened zip containing the parent directory.
      \param dir The full path to the directory to pack.
      \param parentDir The full path to the directory corresponding to
      the root of the ZIP.
      \param prefix Prefix added to all paths inside the archive
      \param filter Filter function that decides whether a particular filename goes into the archive
      \return true if success, false otherwise.
      */
    static bool compressSubDir(QuaZip *parentZip, QString dir, QString parentDir, QSet<QString> &added, QString prefix = QString(),
                               const FilterFunction filter = nullptr);
public:
    /// Extract a single file.
    /**
      \param fileCompressed The name of the archive.
      \param fileName The file to extract.
      \param fileDest The destination file, assumed to be identical to
      \a file if left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */
    static QString extractFile(QString fileCompressed, QString fileName, QString fileDest = QString());
    static QString extractFile(QuaZip &zip, QString fileName, QString fileDest);
    static bool extractFile(QuaZip* zip, QString fileName, QString fileDest);

    /// Extract a list of files.
    /**
      \param fileCompressed The name of the archive.
      \param files The file list to extract.
      \param dir The directory to put the files to, the current
      directory if left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */
    static QStringList extractFiles(QString fileCompressed, QStringList files, QString dir = QString());
    static QStringList extractFiles(QuaZip &zip, const QStringList &files, const QString &dir);

    /// Extract a whole archive.
    /**
      \param fileCompressed The name of the archive.
      \param dir The directory to extract to, the current directory if
      left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */
    static QStringList extractDir(QString fileCompressed, QString dir = QString());
    static QStringList extractDir(QuaZip &zip, const QString &dir);

    /// Get the file list.
    /**
      \return The list of the files in the archive, or, more precisely, the
      list of the entries, including both files and directories if they
      are present separately.
      */
    static QStringList getFileList(QString fileCompressed);
    static QStringList getFileList(QIODevice *ioDevice);
    static QStringList getFileList(QuaZip *zip);

    /// Extract a single file.
    /**
      \param ioDevice pointer to device with compressed data.
      \param fileName The file to extract.
      \param fileDest The destination file, assumed to be identical to
      \a file if left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */
    static QString extractFile(QIODevice *ioDevice, QString fileName, QString fileDest = QString());

    /// Extract a list of files.
    /**
      \param ioDevice pointer to device with compressed data.
      \param files The file list to extract.
      \param dir The directory to put the files to, the current
      directory if left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */
    static QStringList extractFiles(QIODevice *ioDevice, QStringList files, QString dir = QString());

    /// Extract a whole archive.
    /**
      \param ioDevice pointer to device with compressed data.
      \param dir The directory to extract to, the current directory if
      left empty.
      \return The list of the full paths of the files extracted, empty on failure.
      */
    static QStringList extractDir(QIODevice *ioDevice, QString dir = QString());
};

#endif /* JLCOMPRESSFOLDER_H_ */
