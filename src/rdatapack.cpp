#include"rdatapack.h"

const size_t rena::RWF_SIZE = 1024 * 1024 * 10;
// read write file size (10Mb)

#if ( RDP_GENERATION < 2 )

rena::rdatapack::rdatapack( std::string _package_name ){
    RDP_Path  = _package_name.append( ".rdp1" ); // this may be changed after all, now in v1.0 this lib will only write package to exe path
    RDPC_Path = RDP_Path + "c"; // Rena Data Pack Config File Path
    std::cout << "DEBUG> RDP_PATH:  " << RDP_Path << std::endl
              << "DEBUG> RDPC_PATH: " << RDPC_Path << std::endl;
    clear_queue( FileList );
    return;
}

#else

rena::rdatapack::rdatapack(){}

rena::rdatapack::~rdatapack(){}

#endif

errno_t rena::rdatapack::append( path_t _file ){
    if ( _access( _file.c_str() , 00 ) != -1 ) // file exists
    {
        FileList.push( _file ); 
        // add new file to the list
        // also in v1.0, only abs-path is supported, but that may be changed

        return RDP_OK; // returning 0 means no error
    }
    return RDP_ERROR; // file not found or unknown error
}

#if ( RDP_GENERATION < 2 )

errno_t rena::rdatapack::pack(){
    wConfig.open( RDPC_Path , std::ios::out ); // write config file

    errno_t wFerr = fopen_s( &wFile , RDP_Path.c_str() , "wb+" );
    // write File err

    if ( wFerr != 0 ) // cannot create package
    {
        std::cerr << "Create .rdp file error!" << std::endl;
        return -1; // package creation error
    }

    uint64_t rOffset = 0;
    uint64_t wOffset = 0;
    // file pointer offset for read and write file

    while ( !FileList.empty() )
    {
        path_t thisfile = FileList.front();
        // get the file path at queue's front

        wConfig << thisfile << std::endl;
        // write this file's path to config

        errno_t rFerr = fopen_s( &rFile , thisfile.c_str() , "rb+" );
        // read File err

        if ( rFerr != 0 ) // read file error
        {
            std::cerr << "Read file " << thisfile << " error!" << std::endl;
            return -1; // read file error, pack failed
        }

        char* buf = new char[RWF_SIZE];
        rOffset = 0;

        fseek( rFile , 0 , SEEK_END ); // set file pointer to file end
        size_t thisfile_size = ftell( rFile ); // get file size
        std::cout << "DEBUG> File " << thisfile << " size is " << thisfile_size << std::endl;
        if ( !thisfile_size ) // read file size error / file is NULL
        {
            std::cerr << "Cannot get file size or file contains nothing" << std::endl;
            return -1; // read file size error / file is NULL , pack failed
        }
        wConfig << thisfile_size << std::endl; 
        // write this file's length to config
        fseek( rFile , 0 , SEEK_SET ); // reset file pointer to file begin
        
        while ( !feof( rFile ) )
        {
            size_t rFNUM = fread( buf , sizeof( char ) , RWF_SIZE , rFile );
            // read file NUM (How much chars are read)
            // read from file
            if ( rFNUM == 0 ) // readin no data any more
            {
                break;
            }

            rOffset += rFNUM;
            wOffset += rFNUM;
            // add rFNUM to offset total

            size_t wFNUM = fwrite( buf , sizeof( char ) , rFNUM , wFile );
            // write File NUM (How much chars are writed)
            // write to package

            fseek( rFile , rOffset , SEEK_SET );
            fseek( wFile , wOffset , SEEK_SET );
            // set file pointers for rFile and wFile
        } // finish read and write this file

        delete[] buf;
        fclose( rFile ); // finish readin this file
        FileList.pop(); // pop this file from filelist
    } 

    fclose( wFile ); // end of file write
    wConfig.close(); // close config write
    return 0;
}

errno_t rena::rdatapack::unpack(){
    rConfig.open( RDPC_Path , std::ios::in ); // read config file

    path_t _pathtemp;
    size_t _sizetemp;
    clear_queue( FileDList ); // clear FileDList
    while ( rConfig >> _pathtemp ) // readin config
    {
        rConfig >> _sizetemp;
        FILED _FILEDtemp;
        _FILEDtemp.path = _pathtemp;
        _FILEDtemp.size = _sizetemp;
        FileDList.push( _FILEDtemp );
    }

    errno_t rFerr = fopen_s( &rFile , RDP_Path.c_str() , "rb+" );
    // read file err

    if ( rFerr != 0 ) // cannot open package
    {
        std::cerr << "Open Package failed!" << std::endl;
        return -1; // package open error
    }

    uint64_t rOffset = 0;
    uint64_t wOffset = 0;
    // file pointer offset for read and write file

    uint64_t rCheckpoint = 0;
    // checkpoint for package read

    while ( !FileDList.empty() )
    {
        path_t thisfile = FileDList.front().path;
        // get the file path at queue's front
        size_t thisfile_size = FileDList.front().size;
        // get the file size at queue's front

        rCheckpoint += thisfile_size;
        // set new checkpoint

        errno_t wFerr = fopen_s( &wFile , thisfile.c_str() , "wb+" );
        // write File err

        if ( wFerr != 0 ) // write file error
        {
            std::cerr << "Create file " << thisfile << " error!" << std::endl;
            return -1; // create file error, unpack failed
        }

        char* buf = new char[RWF_SIZE];
        wOffset = 0;

        while ( rOffset < rCheckpoint )
        {
            size_t rFNUM;
            // read file NUM (How much chars are read)
            if ( rOffset + RWF_SIZE > rCheckpoint )
            {
                rFNUM = rCheckpoint - rOffset;
            }
            else
            {
                rFNUM = RWF_SIZE;
            }

            fread( buf , sizeof( char ) , rFNUM , rFile );

            rOffset += rFNUM;
            wOffset += rFNUM;
            // add rFNUM to offset total

            size_t wFNUM = fwrite( buf , sizeof( char ) , rFNUM , wFile );
            // write File NUM (How much chars are writed)
            // write to file

            fseek( rFile , rOffset , SEEK_SET );
            fseek( wFile , wOffset , SEEK_SET );
            // set file pointers for rFile and wFile
        } // finish read and write this file

        delete[] buf;
        fclose( wFile ); // finish write this file
        FileDList.pop(); // pop this file from fileDList
    }

    fclose( rFile ); // end of package read
    rConfig.close(); // close config read
    return 0;

}

#else

/**
 * 
 */
errno_t rena::rdatapack::AddFileToZip( zipFile zfile , const std::string& file_name_in_zip , const std::string& file ){
    if ( zfile == NULL || file_name_in_zip.empty() )
    {
        std::cerr << "ERROR: In rdatapack::AddFileToZip: empty zipFile or file dir in zipFile" << std::endl;
        return RDP_ERROR;
    }

    errno_t nErr;
    zip_fileinfo zinfo = { 0 };
    tm_zip tmz = { 0 };
    zinfo.tmz_date = tmz;
    zinfo.dosDate = 0;
    zinfo.internal_fa = 0;
    zinfo.external_fa = 0;

    char FileNameInZip[_MAX_PATH] = { 0 };
    memset( FileNameInZip , 0x00 , sizeof( FileNameInZip ) );
    strcat_s( FileNameInZip , file_name_in_zip.c_str() );
    // copy file name in zip

    if ( file.empty() ) // file path empty, create one empty folder in zip
    {
        strcat_s( FileNameInZip , "\\" );
    }

    nErr = zipOpenNewFileInZip( zfile , FileNameInZip , &zinfo , NULL , 0 , NULL , 0 , NULL , Z_DEFLATED , Z_DEFAULT_COMPRESSION );

    if ( nErr != Z_OK )
    {
        std::cerr << "ERROR: In rdatapack::AddFileToZip: When calling zipOpenNewFileInZip, error " << nErr << " occurs" << std::endl;
        return RDP_ERROR;
    }
    
    if ( !file.empty() ) // file path do contain one file
    {
        FILE* rFile = fopen( file.c_str() , "rb" );

        if ( rFile == NULL ) // open file failed
        {
            std::cerr << "ERROR: In rdatapack::AddFileToZip: When opening file " << file << " , error " << GetLastError() << " occurs" << std::endl;
            return RDP_ERROR;
        }

        size_t rBytesNUM = 0;
        char* buf = new char[RWF_SIZE];
        // create file readin buffer

        if ( buf == NULL )
        {
            std::cerr << "ERROR: In rdatapack::AddFileToZip: When creating file readin buffer, error " << GetLastError() << " occurs" << std::endl;
            return RDP_ERROR;
        }

        while ( !feof( rFile ) ) // read file to buf and then write to zip
        {
            memset( buf , 0x00 , sizeof( buf ) );
            rBytesNUM = fread( buf , sizeof( char ) , sizeof( buf ) , rFile );
            nErr = zipWriteInFileInZip( zfile , buf , rBytesNUM );
            if ( ferror( rFile ) )
            {
                break;
            }
        }

        if ( buf )
        {
            delete[] buf;
            buf = NULL;
        }
        if ( rFile )
        {
            fclose( rFile );
            rFile = NULL;
        }
    }

    zipCloseFileInZip( zfile );
    return RDP_OK;
}

#endif

#pragma region operator

rena::rdatapack& rena::operator<<( rdatapack& _dp , path_t _file ){
    _dp.append( _file ); // data package
    return _dp;
}

// this is still in progress (the operation now is only a test for it's function)
rena::rdatapack& rena::operator<<( rdatapack& _dp , _Setpt _pt ){
    _dp.pt = _pt; 
    return _dp;
}

rena::rdatapack& rena::operator+( rdatapack& _dp , path_t _file ){
    _dp.append( _file ); //data package
    return _dp;
}

#pragma endregion operator



void rena::rdatapack::test( zipFile zp , const std::string fnz, const std::string fn ){
    AddFileToZip( zp , fnz , fn );
}



void rena::rdatapack::clear_queue( std::queue <path_t>& q ){
    std::queue <path_t> empty;
    std::swap( empty , q );
    return;
}

void rena::rdatapack::clear_queue( std::queue <FILED>& q ){
    std::queue <FILED> empty;
    std::swap( empty , q );
    return;
}