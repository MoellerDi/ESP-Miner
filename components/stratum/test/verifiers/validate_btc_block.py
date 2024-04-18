import hashlib
from binascii import unhexlify, hexlify

"""
Genesis block data from https://blockchain.info/rawblock/000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f
"""
btc_version = 1
hex_prev_hash = "0000000000000000000000000000000000000000000000000000000000000000"
hex_merkle_hash = "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"
epoch_time = 1231006505
bits = 486604799
nonce = 2083236893

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

