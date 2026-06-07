//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//

#if !defined(CONFIG_HPP_9274927)
#define CONFIG_HPP_9274927

#include <windows.h>
#include <wincrypt.h>
#include <string>

//  Config provides configuration properties for the whole project.
//  Implemented as a singleton object.
//
//  Use as follows:
//      CONFIG().SomeConfigProperty();
//
//  Configuration properties do not need to be hardcoded,
//  but can be read from the registry, for example.
//

class ConfigSingleton;

class Config
{
    friend class ConfigSingleton;

public:
    ALG_ID CryptAlgorithm() const
    {
        return CALG_AES_128;
    }

    DWORD CryptProviderType() const
    {
        return PROV_RSA_AES;
    }

    std::wstring AuthResetKeyName() const
    {
        return L"Comm\\Security\\Policy\\LASSD\\AuthReset\\SimReset";
    }

    std::wstring AuthResetValName() const
    {
        return L"Passcode";
    }

    std::wstring SimResultValName() const
    {
        return L"SimResult";
    }

    HKEY AuthResetRootKey() const
    {
        return HKEY_LOCAL_MACHINE;
    }

private:
    Config() {}
    Config(Config const &);
    Config & operator=(Config const &);
};

class ConfigSingleton
{
public:
    static Config & instance()
    {
        static Config config;
        return config;
    }
};

#define CONFIG ConfigSingleton::instance

#endif  // CONFIG_HPP_9274927
