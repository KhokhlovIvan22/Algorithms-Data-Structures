import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int[][] adjacency = new int[n][n];
        for (int i = 0; i < n; ++i)
            Arrays.fill(adjecency[i], 0);
        int m = Integer.parseInt(st.nextToken());
        int u,v;
        for (int i=0;i<m;++i)
        {
            st = new StringTokenizer(br.readLine());
            u = Integer.parseInt(st.nextToken());
            v = Integer.parseInt(st.nextToken());
            adjacency[u-1][v-1]=1;
            adjacency[v-1][u-1]=1;
        }
        PrintWriter out = new PrintWriter("output.txt");
        for (int i=0; i<n; ++i) {
            for (int j = 0; j < n; ++j)
                out.print(adjcency[i][j] + " ");
            out.print("\n");
        }
        out.close();
    }
}
