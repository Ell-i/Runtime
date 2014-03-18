#define SPI_XFER_RX(op, reg, xtra)  spi_command((op) | ((reg) & ENC_REG_MASK), 0, (xtra))
#define SPI_XFER_TX(op, reg, value) spi_command((op) | ((reg) & ENC_REG_MASK), (value), 0)

inline int
ENC28J60Class::reg_get(enc_reg_t reg) const {
    int xfer_3rd_byte = 0;
    int value;

    spi_activate();

    switch (reg & ENC_TYPE_MASK) {
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
        xfer_3rd_byte = 1;
        /* FALLTHROUGH */
    case ENC_BANK0:
    case ENC_BANK1:
    case ENC_BANK2:
    case ENC_BANK3:
        set_bank(reg & ENC_BANK_MASK);
        /* FALLTHROUGH */
    case ENC_BANK_GEN:
        value = SPI_XFER_RX(ENC_SPI_READ_REG, reg, xfer_3rd_byte);
        if (reg & ENC_TYPE_LONG)
            value |= SPI_XFER_RX(ENC_SPI_READ_REG, reg+1, xfer_3rd_byte) << 8;
        break;
    case ENC_BANK_PHY:
        value = phy_get(static_cast<enc_reg_t>(reg & ENC_REG_MASK));
    default:
        abort();
    }

    spi_deactivate();

    return value;
}

inline void
ENC28J60Class::reg_set(enc_reg_t reg, int value) const {
    spi_activate();

    switch (reg & ENC_TYPE_MASK) {
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
    case ENC_BANK0:
    case ENC_BANK1:
    case ENC_BANK2:
    case ENC_BANK3:
        set_bank(reg & ENC_BANK_MASK);
        /* FALLTHROUGH */
    case ENC_BANK_GEN:
        SPI_XFER_TX(ENC_SPI_WRITE_REG, reg, value);
        if (reg & ENC_TYPE_LONG)
            SPI_XFER_TX(ENC_SPI_WRITE_REG, reg+1, value >> 8);
        break;
    case ENC_BANK_PHY:
        phy_set(static_cast<enc_reg_t>(reg & ENC_REG_MASK), value, 0);
        break;
    default:
        abort();
    }
    spi_deactivate();
}

inline void
ENC28J60Class::reg_bitop(enc_spi_op_t bitop, enc_reg_t reg, int mask) const {
    //assert(bitop == ENC_SPI_SET_BF || bitop == ENC_SPI_CLR_BF);
    spi_activate();

    switch (reg & ENC_TYPE_MASK) {
    case ENC_BANK0:
    case ENC_BANK1:
    case ENC_BANK2:
    case ENC_BANK3:
        set_bank(reg & ENC_BANK_MASK);
        /* FALLTHROUGH */
    case ENC_BANK_GEN:
        SPI_XFER_TX(bitop, reg, mask);
        if (reg & ENC_TYPE_LONG)
            SPI_XFER_TX(bitop, reg, mask >> 8);
        break;
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
    case ENC_BANK_PHY:
    default:
        abort();
    }
    spi_deactivate();
}

/**
 * Switches to the right register bank
 * if not there already
 */
inline void
ENC28J60Class::set_bank(int bank) const {
    static uint8_t curr = ENC_BANK0; /* Current bank */

    bank &= ENC_BANK_MASK;

    if (curr == bank || bank == ENC_BANK_GEN)
        return;

    register int bank_index = (bank & ENC_BANK_MASK) >> ENC_BANK_SHIFT;
    register int curr_index = (curr & ENC_BANK_MASK) >> ENC_BANK_SHIFT;

    register const int bits_to_clr = (curr_index  & ~bank_index);
    if (bits_to_clr != 0)
        SPI_XFER_TX(ENC_SPI_CLR_BF, E_CON1, bits_to_clr);

    register const int bits_to_set = (~curr_index &  bank_index);
    if (bits_to_set != 0)
        SPI_XFER_TX(ENC_SPI_SET_BF, E_CON1, bits_to_set);

    curr = bank;
}
