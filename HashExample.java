import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class HashExample {
    public static void main(String[] args) {
        String password = "examplePassword";
        String hashedPassword = hashPassword(password);
        System.out.println("Original Password: " + password);
        System.out.println("Hashed Password: " + hashedPassword);
    }

    public static String hashPassword(String password) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(password.getBytes());
            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) {
                hexString.append(String.format("%02x", b));
            }
            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}
