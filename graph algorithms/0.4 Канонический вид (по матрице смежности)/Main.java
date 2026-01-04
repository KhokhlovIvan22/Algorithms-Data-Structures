import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int[] tree = new int[n];
        Arrays.fill(tree,0);
        for (int i = 0; i < n; ++i)
        {
            st = new StringTokenizer(br.readLine());
            for (int j=0;j<n;++j)
            {
                int arc = Integer.parseInt(st.nextToken());
                if (arc==1)
                    tree[j]=i+1;
            }
        }
        PrintWriter out = new PrintWriter("output.txt");
        for (int i = 0; i < n; ++i)
            out.print(tree[i]+" ");
        out.close();
    }
}
