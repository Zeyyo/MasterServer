#pragma once

namespace Utilities::Crypto
{
	using CryptoPP::SecByteBlock;

	std::string SecByteBlockToStringEncode(const SecByteBlock& block);
	SecByteBlock StringToSecByteBlockDecode(const std::string& encodedString);
}
