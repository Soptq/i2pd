/*
* Copyright (c) 2013-2020, The PurpleI2P Project
*
* This file is part of Purple i2pd project and licensed under BSD3
*
* See full license text in LICENSE file at top of project tree
*/

#ifndef API_H__
#define API_H__

#include <memory>
#include <iostream>
#include "Identity.h"
#include "Destination.h"
#include "Streaming.h"

namespace i2p
{
namespace api
{
	// initialization start and stop
	void InitI2P (int argc, char* argv[], const char * appName, std::shared_ptr<std::ostream> logstream = nullptr);
	void StartI2P ();

	// write system log to logStream, if not specified to <appName>.log in application's folder
    void CloseAcceptsTunnels ();
	void StopI2P ();
	void RunPeerTest (); // should be called after UPnP

    // fetch tunnels info
    int GetClientTunnelsCount ();
    int GetServerTunnelsCount ();
    int GetClientTunnelsName (std::string& name, int index);
    int GetClientTunnelsIdent (std::string& ident, int index);
    int GetServerTunnelsName (std::string& name, int index);
    int GetServerTunnelsIdent (std::string& ident, int index);

	// destinations
	std::shared_ptr<i2p::client::ClientDestination> CreateLocalDestination (const i2p::data::PrivateKeys& keys, bool isPublic = true,
		const std::map<std::string, std::string> * params = nullptr);
	std::shared_ptr<i2p::client::ClientDestination> CreateLocalDestination (bool isPublic = false, i2p::data::SigningKeyType sigType = i2p::data::SIGNING_KEY_TYPE_ECDSA_SHA256_P256,
		const std::map<std::string, std::string> * params = nullptr); // transient destinations usually not published
	void DestroyLocalDestination (std::shared_ptr<i2p::client::ClientDestination> dest);

	// streams
	void RequestLeaseSet (std::shared_ptr<i2p::client::ClientDestination> dest, const i2p::data::IdentHash& remote);
	std::shared_ptr<i2p::stream::Stream> CreateStream (std::shared_ptr<i2p::client::ClientDestination> dest, const i2p::data::IdentHash& remote);
	void AcceptStream (std::shared_ptr<i2p::client::ClientDestination> dest, const i2p::stream::StreamingDestination::Acceptor& acceptor);
	void DestroyStream (std::shared_ptr<i2p::stream::Stream> stream);

    // keys
    int LoadPrivateKeysFromFile (std::string& idenHashB32, const std::string& filename, i2p::data::SigningKeyType sigType, i2p::data::CryptoKeyType cryptoType);
}
}

#endif
