
#pragma once

UENUM(BlueprintType)
/*
 * List of serialization formats supported by UGameDataBase-derived classes.
 */
enum class EGameDataFormat : uint8
{
	/*
	 * JSON text format. See https://www.json.org/
	 */
	Json,
	/*
	 * MessagePack binary format. See https://msgpack.org/
	 */
	MessagePack
};


