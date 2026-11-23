import java.io.*;
import java.net.*;

public class ScoreClient {

    private static final String SERVER_IP = "192.168.1.33";
    private static final int PORT = 9011;

    public static void main(String[] args) throws Exception {

        String studentName = "Student B";

        if (args.length > 0) {
            studentName = args[0];
        }

        Socket socket = new Socket(SERVER_IP, PORT);

        PrintWriter writer = new PrintWriter(
            socket.getOutputStream(), true
        );

        BufferedReader reader = new BufferedReader(
            new InputStreamReader(socket.getInputStream())
        );

        writer.println(studentName);

        String response = reader.readLine();

        System.out.println("Server response: " + response);

        socket.close();
    }
}
