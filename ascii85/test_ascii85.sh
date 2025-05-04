#!/bin/bash

dd if=/dev/random bs=2K count=1 status=none of=random.bin

python3 -c '
import sys
import base64
sys.stdout.buffer.write(base64.a85encode(sys.stdin.buffer.read()))
' <random.bin >random.a85

./ascii85 -e <random.bin >random.a85.test
if ! cmp -s random.a85 random.a85.test; then
  echo "[FAIL] Encoder gives wrong output!"
  exit 1
fi

./ascii85 -d <random.a85 >random.bin.test
if ! cmp -s random.bin random.bin.test; then
  echo "[FAIL] Decoder gives wrong output!"
  exit 1
fi

echo "[OK] All tests passed!"
exit 0
