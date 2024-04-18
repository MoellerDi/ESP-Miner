import hashlib
from binascii import unhexlify, hexlify

"""
Genesis block data from https://blockchain.info/rawblock/000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f
"""
btc_version = 537944064
hex_prev_hash = "00000000000000000001cde81f5ade7ecd5f5f20ba1df8fde27c145463461e09"
hex_merkle_hash = "2836bac5721062dfec270ebf9b554d002612ab6c1a0c05bd43d471892496c205"
epoch_time = 1713376819
bits = 0x17034219
nonce = 1720357422

def endian_big_to_little(hex):
    padded_hex = ''
    if len(hex) != 8:
        padding_len = 8 - len(hex)
        for num in range(padding_len):
            padded_hex += '0'
        padded_hex += str(hex)
    else:
        padded_hex = hex
    ba = bytearray.fromhex(padded_hex)
    ba.reverse()
    le_hex = ''.join(format(x, '02x') for x in ba)
    return le_hex

hex_btc_version = endian_big_to_little(hex(btc_version)[2:])
hex_prev_hash = endian_big_to_little(hex_prev_hash)
hex_merkle_hash = endian_big_to_little(hex_merkle_hash)
hex_time = endian_big_to_little(hex(int(epoch_time))[2:])
hex_bits = endian_big_to_little(hex(bits)[2:])
hex_nonce = endian_big_to_little(hex(nonce)[2:])

header_hex = (
    hex_btc_version +
    hex_prev_hash +
    hex_merkle_hash +
    hex_time +
    hex_bits +
    hex_nonce
)

header_bin = unhexlify(header_hex)
hash = hashlib.sha256(hashlib.sha256(header_bin).digest()).digest()
print(hexlify(hash[::-1]).decode("utf-8"))

