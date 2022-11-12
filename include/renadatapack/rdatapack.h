#ifndef _RDATAPACK_H_
#define _RDATAPACK_H_

#include<iostream>
#include<cstdio>
#include<string>
#include<fstream>
#include<queue>
#include<io.h>

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

    class rdatapack{
        public:
            rdatapack( std::string );

            errno_t append( path_t );

            errno_t pack();
            errno_t unpack();

            friend rdatapack& operator<<( rdatapack& , path_t );
            friend rdatapack& operator+( rdatapack& , path_t );

//          void test();

        private:
            std::ifstream rConfig;
            std::ofstream wConfig;
            FILE *rFile;
            FILE *wFile;

            std::queue <path_t> FileList;
            std::queue <FILED>  FileDList;

            path_t RDP_Path;
            path_t RDPC_Path;

            void clear_queue( std::queue <path_t>& );
            void clear_queue( std::queue <FILED>& );
    };

    rdatapack& operator<<( rdatapack& , path_t );
    rdatapack& operator+( rdatapack& , path_t );

} // namespace rena

#endif