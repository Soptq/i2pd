/*
* Copyright (c) 2013-2020, The PurpleI2P Project
*
* This file is part of Purple i2pd project and licensed under BSD3
*
* See full license text in LICENSE file at top of project tree
*/

#include "api.h"
#include "capi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static std::string RET_STR;

// Uses the example from: https://stackoverflow.com/a/9210560
// See also https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c/9210560#
// Does not handle consecutive delimiters, this is only for passing
// lists of arguments by value to InitI2P from C_InitI2P
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char**) malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


#ifdef __cplusplus
extern "C" {
#endif

void C_InitI2P (int argc, char argv[], const char * appName)
{
	const char* delim = " ";
	char* vargs = strdup(argv);
	char** args = str_split(vargs, *delim);
//    std::shared_ptr<std::ostream> p_cout(&std::cout, [](std::ostream*){});
	return i2p::api::InitI2P(argc, args, appName, nullptr);
}

void C_StartI2P ()
{
	return i2p::api::StartI2P();
}

void C_CloseAcceptsTunnels () {
    return i2p::api::CloseAcceptsTunnels();
}

void C_StopI2P ()
{
	return i2p::api::StopI2P();
}

void C_RunPeerTest ()
{
	return i2p::api::RunPeerTest();
}

int C_GetClientTunnelsCount ()
{
    int ret = i2p::api::GetClientTunnelsCount();
    return ret;
}

int C_GetServerTunnelsCount ()
{
    int ret = i2p::api::GetServerTunnelsCount();
    return ret;
}

const char * C_GetClientTunnelsName (int index)
{
    if (index < C_GetClientTunnelsCount())
    {
        int ret = i2p::api::GetClientTunnelsName(RET_STR, index);
        if (ret == 1)
        {
            return RET_STR.c_str();
        } else
        {
            return NULL;
        };
    }
    return NULL;
}

const char * C_GetClientTunnelsIdent (int index)
{
    if (index < C_GetClientTunnelsCount())
    {
        int ret = i2p::api::GetClientTunnelsIdent(RET_STR, index);
        if (ret == 1)
        {
            return RET_STR.c_str();
        } else
        {
            return NULL;
        };
    }
    return NULL;
}

const char * C_GetServerTunnelsName (int index)
{
    if (index < C_GetServerTunnelsCount())
    {
        int ret = i2p::api::GetServerTunnelsName(RET_STR, index);
        if (ret == 1)
        {
            return RET_STR.c_str();
        } else
        {
            return NULL;
        };
    }
    return NULL;
}

const char * C_GetServerTunnelsIdent (int index)
{
    if (index < C_GetServerTunnelsCount())
    {
        int ret = i2p::api::GetServerTunnelsIdent(RET_STR, index);
        if (ret == 1)
        {
            return RET_STR.c_str();
        } else
        {
            return NULL;
        };
    }
    return NULL;
}

const char * C_LoadPrivateKeysFromFile (const char * filename, uint16_t sigType, uint16_t cryptoType)
{
    std::string str_filename(filename);
    int ret = i2p::api::LoadPrivateKeysFromFile(RET_STR, str_filename, sigType, cryptoType);
    if (ret == 1)
    {
        return RET_STR.c_str();
    } else
    {
        return NULL;
    }
}

#ifdef __cplusplus
}
#endif
