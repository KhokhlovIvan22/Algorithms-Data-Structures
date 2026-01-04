import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int[] tree = new int[n];
            Arrays.fill(tree, 0);
        int u,v;
        for (int i=0;i<n-1;++i)
        {
            st = new StringTokenizer(br.readLine());
            u = Integer.parseInt(st.nextToken());
            v = Integer.parseInt(st.nextToken());
            tree[v-1]=u;
        }
        PrintWriter out = new PrintWriter("output.txt");
        for (int i=0; i<n; ++i)
                out.print(tree[i] + " ");
        out.close();
    }
}
