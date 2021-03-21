template <typename T> std::string SerialPort::formatVal(T val, int type) {
    std::ostringstream os;

    switch (type) {
        case BIN: {
            std::bitset<8 * sizeof(val)> bits(val);
            os << bits;
            break;
        }

        case HEX: {
            os << std::hex << val;
            break;
        }

        case OCT: {
            os << std::oct << val;
            break;
        }

        default: {
            os << val;
            break;
        }
    }

    return os.str();
}
