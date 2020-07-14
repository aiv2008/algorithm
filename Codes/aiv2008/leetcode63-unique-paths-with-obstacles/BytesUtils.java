class BytesUtils {

/**
     * 高位字节数组转int,低字节在前.
     * -------------------------------------------
     * |  0-7位  |  8-16位  |  17-23位  |  24-31位 |
     * -------------------------------------------
     *
     * @param src 字节数组
     * @return int值
     */
    public static int highBytesToInt(byte[] src) {
        return highBytesToInt(src, 0, src.length);
    }

    /**
     * 高位字节数组转long,低字节在前.
     * -------------------------------------------
     * |  0-7位  |  8-16位  |  17-23位  |  24-31位 |
     * -------------------------------------------
     *
     * @param src 字节数组
     * @return int值
     */
    public static int highBytesToInt(byte[] src, int offset, int len) {
        int n = 0;
        len = Math.min(len, 4);
        for (int i = 0; i < len; i++) {
            int left = i * 8;
            n += ((src[i + offset] & 0xFF) << left);
        }
        return n;
    }

    public static void main(String[] args){
	  // byte
    }
}
