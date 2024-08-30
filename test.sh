#!/bin/bash

# Path to the configuration file
CONFIG_FILE="config.txt"

# Base configuration (number of keys, type of keys, size of keys (min, max), size of values (min, max), serialization function)
BASE_CONFIG="8, string, 8, 8, 16, 16, 100"

# Variations
KEY_TYPES=("int32_t" "double")
NUM_KEYS=("16" "32" "64")
KEY_SIZES=("4" "16" "32")
VALUE_SIZES=("32" "64" "128")

# KEY_TYPES=("int32_t" "double" "string")
# NUM_KEYS=("8" "16" "32" "64")
# KEY_SIZES=("4" "8" "16" "32")
# VALUE_SIZES=("16" "32" "64" "128")

# Function to run the test with the provided configuration
run_test() {
    local config="$1"
    echo "Running test with config: $config"
    echo "${config}
# nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, testSize, serialization_function
# nkey: number of keys | tkey: type of keys | skey: size of keys (min, max) | sval: size of values
# supported types(tkey): int32_t, double, string
# sval only uses when the type(tkey) is string
# string means: char {variable length = skey} [{sval + 1}]
# adding 1 in sval means it needs a space for null character
# serialization_function names:
# JSON, MP (MessagePack), FX (FlexBuffers), PB (Protocol Buffers), TH (Apache Thrift), FB (FlatBuffers)" > $CONFIG_FILE
    ./run.sh
}

rm -rf ./tmp/*

echo "Running base test"
echo "${BASE_CONFIG}"
run_test "${BASE_CONFIG}"
rm -rf ./tmp/*

# Change key types
for type in "${KEY_TYPES[@]}"; do
    config="8, $type, 8, 8, 16, 16, 100"
    run_test "$config"
    rm -rf ./tmp/*
done

# Change number of keys
for keys in "${NUM_KEYS[@]}"; do
    config="$keys, string, 8, 8, 16, 16, 100"
    run_test "$config"
    rm -rf ./tmp/*
done

# Change key sizes
for key_size in "${KEY_SIZES[@]}"; do
    config="8, string, $key_size, $key_size, 16, 16, 100"
    run_test "$config"
    rm -rf ./tmp/*
done

# Change value sizes
for value_size in "${VALUE_SIZES[@]}"; do
    config="8, string, 8, 8, $value_size, $value_size, 100"
    run_test "$config"
    rm -rf ./tmp/*
done