import java.io.*;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.StringTokenizer;

public class Main {
    public static int[][] adjacency;
    public static int[] order;
    public static boolean[] visited;
    public static int ord = 0;
    public static void bfs (int start, int n)
    {
        Queue<Integer> q = new ArrayDeque<>();
        visited[start]=true;
        ord++;
        order[start]=ord;
        q.add(start);
        while (!q.isEmpty())
        {
            int v = q.poll();
            for (int i=0;i<n;++i)
                if (adjacency[v][i]==1 && visited[i]==false)
                {
                    q.add(i);
                    visited[i]=true;
                    ord++;
                    order[i]=ord;
                }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        adjacency = new int[n][n];
        order = new int[n];
        visited = new boolean[n];
        for (int i=0;i<n;++i)
        {
            st = new StringTokenizer(br.readLine());
            for (int j=0;j<n;++j)
                adjacency[i][j]=Integer.parseInt(st.nextToken());
        }
        for (int i=0;i<n;++i)
            if (order[i]==0)
                bfs(i,n);
        PrintWriter out = new PrintWriter("output.txt");
        for (int i = 0; i < n; i++)
            out.print(order[i]+" ");
        out.close();
    }
}
