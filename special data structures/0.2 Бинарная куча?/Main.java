import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("input.txt"));
        PrintWriter out = new PrintWriter(new File("output.txt"));
        int n = in.nextInt();
        int[] minHeap = new int[n+1];
        for (int i=1;i<n+1;++i)
            minHeap[i]=in.nextInt();
        int i=1;
            while(2*i<=n)
        {
            if (2*i+1<=n) {
                if (minHeap[i] > minHeap[2 * i] || minHeap[i] > minHeap[2 * i + 1]) {
                    out.print("NO");
                    out.close();
                    return;
                }
            }
            else {
                if (minHeap[i] > minHeap[2 * i]) {
                    out.print("NO");
                    out.close();
                    return;
                }
            }
                i++;
        }
            out.print("YES");
            out.close();
    }
}
