#include "NEtw_pch.h"

#include "cryptlib.h"
#include "hex.h"
#include <secblock.h>
#include <filters.h>
#include "HexEncDec.h"

namespace Utilities::Crypto
{
	using CryptoPP::HexEncoder;
	using CryptoPP::StringSink;
	using CryptoPP::StringSource;
	using CryptoPP::HexDecoder;
	using CryptoPP::ArraySink;
	using CryptoPP::byte;

	std::string SecByteBlockToStringEncode(const SecByteBlock& block) {
		std::string result;
		result.clear();
		HexEncoder encoder(new StringSink(result));
		encoder.Put(block.data(), block.size());
		encoder.MessageEnd();
		return result;
	}
	SecByteBlock StringToSecByteBlockDecode(const std::string& encodedString) 
	{
		std::string tempBuffer;
		tempBuffer.clear();
		StringSource(encodedString, true,
			new HexDecoder(
				new StringSink(tempBuffer)
			)
		);
		SecByteBlock result((const byte*)tempBuffer.data(), tempBuffer.size());
		return result;
	}
}