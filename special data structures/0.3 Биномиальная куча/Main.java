import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        long n = in.nextLong();
        long k=0;
        while (n!=0)
        {
            if (n%2!=0)
                out.println(k);
            n=n>>1;
            k++;
        }
        out.close();
    }
}
