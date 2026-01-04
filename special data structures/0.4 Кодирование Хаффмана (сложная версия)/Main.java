import java.io.*;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("huffman.in"));
        int n = Integer.parseInt(br.readLine().trim());
        StringTokenizer st = new StringTokenizer(br.readLine());
        long[] leaves = new long[n];
        for (int i = 0; i < n; ++i)
            leaves[i] = Integer.parseInt(st.nextToken());
        long[] vertices = new long[n - 1];
        int i = 0;
        int j = 0;
        int k = 0;
        long sum = 0;
        while (k < n - 1) {
            long term1, term2;
            if (i < n && (j >= k || leaves[i] <= vertices[j]))
                term1 = leaves[i++];
            else
                term1 = vertices[j++];
            if (i < n && (j >= k || leaves[i] <= vertices[j]))
                term2 = leaves[i++];
            else
                term2 = vertices[j++];
            vertices[k++] = term1 + term2;
            sum += term1 + term2;
        }
        BufferedWriter bw = new BufferedWriter(new FileWriter("huffman.out"));
        bw.write(Long.toString(sum));
        bw.close();
    }
}
