import java.io.*;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        ArrayList<ArrayList<Integer>> adjacency = new ArrayList<>();
        for (int i = 0; i < n; ++i)
            adjacency.add(new ArrayList<>());
        int u,v;
        for (int i = 0; i < m; ++i)
        {
            st = new StringTokenizer(br.readLine());
            u = Integer.parseInt(st.nextToken());
            v = Integer.parseInt(st.nextToken());
            adjacency.get(u - 1).add(v);
            adjacency.get(v - 1).add(u);
        }
        PrintWriter out = new PrintWriter("output.txt");
        for (int i = 0; i < n; i++)
        {
            ArrayList<Integer> neighbors = adjacency.get(i);
            out.print(neighbors.size());
            for (int x: neighbors)
                out.print(" " + x);
            out.println();
        }
        out.close();
    }
}
