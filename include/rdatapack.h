#ifndef _RDATAPACK_H_
#define _RDATAPACK_H_

#include<iostream>
#include<cstdio>
#include<string>
#include<fstream>
#include<queue>
#include<io.h>
#include<errhandlingapi.h>

//#include<minizip-ng/zip.h>
//#include<minizip-ng/unzip.h>
#include"zip.h"
#include"unzip.h"
#include"zlib.h"

#define RDP_GENERATION 2
#define RDP_VERSION "2.0.0"

#define RDP_OK 0
#define RDP_ERROR ( -1 )

#define RDP_OFF false
#define RDP_ON  true

#define STRICT_RETURN RDP_OFF
#define TURN_ON_DEBUG RDP_ON

#if ( STRICT_RETURN ) // this part is still in progress

    #define R_CREATE_BUF_ERR ( -0x0001 )
    #define R_FILE_OPEN_ERR  ( -0x0002 )

#endif

namespace rena{

    extern const size_t RWF_SIZE;

    typedef std::string         path_t;
    typedef int                 int32_t;
    typedef unsigned int        uint32_t;
    typedef long long           int64_t;
    typedef unsigned long long  uint64_t;
    typedef enum {
        folder,
        file
    }                           PTYPE; // Path Type
    typedef struct {
        path_t path;
        size_t size;
    }                           FILED; // File Data

    struct _Setpt{
        PTYPE __pt;
    };

    inline _Setpt setpt( PTYPE __n ){
        return { __n };
    }

#pragma region class_rdatapack

    class rdatapack{
        public:
            rdatapack();
            ~rdatapack();

            errno_t append( path_t );

//          errno_t pack();
//          errno_t unpack();

            friend rdatapack& operator<<( rdatapack& , path_t );
            friend rdatapack& operator<<( rdatapack& , _Setpt );
            friend rdatapack& operator+( rdatapack& , path_t );

            void test( zipFile , const std::string , const std::string );

        private:
            static errno_t AddFileToZip( zipFile , const std::string& , const std::string& );

//          std::ifstream rConfig;
//          std::ofstream wConfig;
//          FILE *rFile;
//          FILE *wFile;

            _Setpt pt;

            std::queue <path_t> FileList;
//          std::queue <FILED>  FileDList;

            path_t RDP_Path;
            path_t RDPC_Path;

            void clear_queue( std::queue <path_t>& );
            void clear_queue( std::queue <FILED>& );
    };

#pragma endregion class_rdatapack

    rdatapack& operator<<( rdatapack& , path_t );
    rdatapack& operator<<( rdatapack& , _Setpt );
    rdatapack& operator+( rdatapack& , path_t );

} // namespace rena

#endif