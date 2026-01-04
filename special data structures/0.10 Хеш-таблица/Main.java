import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int m = Integer.parseInt(st.nextToken());
        int hashTable[] = new int[m];
        Arrays.fill(hashTable, -1);
        int c = Integer.parseInt(st.nextToken());
        int n = Integer.parseInt(st.nextToken());
        for (int j = 0; j < n; ++j) {
            st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int i = 0, h;
            do {
                h = ((x % m) + c * i) % m;
                i++;
                if (hashTable[h]==x)
                    break;
            }
            while (hashTable[h] != -1);
            hashTable[h]=x;
        }
        PrintWriter out = new PrintWriter("output.txt");
        for (int i=0;i<m;++i)
            out.print(hashTable[i]+" ");
        out.close();
    }
}
