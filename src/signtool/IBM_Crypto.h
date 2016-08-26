/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/signtool/IBM_Crypto.h $                                   */
/*                                                                        */
/* OpenPOWER sb-signing-utils Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2016                             */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#ifndef __IBM_CRYPTO_H_
#define __IBM_CRYPTO_H_

#include <vector>
#include <string>

#include "IBM_HexString.h"
#include "IBM_Utils.h"

class IBM_Crypto
{
public:
    IBM_Crypto( const std::string& p_mode );
    virtual ~IBM_Crypto();

    bool Sign( const std::string& p_pKeyName,
               const std::string& p_digest,
               const std::string& p_signFileName,
               const std::string& p_saHostName,
               int                p_saPortNum );

    int Verify( const std::string& p_pubKeyFileName,
                const std::string& p_digest,
                const std::string& p_signFileName );

    bool CreateKeyPair( const std::string& p_privKeyFileName,
                        const std::string& p_pubKeyFileName );

    bool ComputeHash( IBM_HashAlgo         p_hashAlgo,
                      const unsigned char* p_data,
                      size_t               p_dataLen,
                      std::string&         p_digestStr );

private:
    // Disallow Copy Constructor and Assignment Operator
    IBM_Crypto( IBM_Crypto& ); 
    IBM_Crypto operator = ( IBM_Crypto& );
    
    virtual bool doCcaSign( const std::string&  p_pKeyName,
                            const IBM_HexBytes& p_dgstBytes,
                            IBM_HexBytes&       p_signBytes,
                            const std::string&  p_serverName,
                            int                 p_serverPort );

    virtual bool doOpensslSign( const std::string&  p_privKeyFileName,
                                const IBM_HexBytes& p_dgstBytes,
                                IBM_HexBytes&       p_signBytes );

    virtual int doCcaVerify( const std::string&  p_pubKeyFileName,
                             const IBM_HexBytes& p_dgstBytes,
                             const std::string&  p_signFileName );

    virtual int doOpensslVerify( const std::string&  p_pubKeyFileName,
                                 const IBM_HexBytes& p_dgstBytes,
                                 const std::string&  p_signFileName );

    std::string  m_mode;
};


struct sign_agent_packet_s
{
    uint8_t     keyname[32];
    uint8_t     digest[32];
} __attribute__((packed));


#endif // __IBM_CRYPTO_H_