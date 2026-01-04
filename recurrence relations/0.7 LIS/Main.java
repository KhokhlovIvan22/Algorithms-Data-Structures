import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    static int A[];
    static int dp[];
    static int dp_length;

    static int upperBound (int key)
    {
        int l = 0;
        int r = dp_length;
        while (l<r) {
            int m = (l + r) / 2;
            if (dp[m]<=key)
                l=m+1;
            else
                r=m;
        }
        return l;
    }

    static int lis (int n)
    {
        dp[0]= Integer.MIN_VALUE;
        Arrays.fill(dp,1,n,Integer.MAX_VALUE);
        dp_length=1;
        for (int i=0;i<n;++i) {
            int j = upperBound(A[i]);
            if (j>0 && dp[j-1]!=A[i]) {
                dp[j] = A[i];
                if (j==dp_length)
                dp_length++;
            }
        }
        return dp_length-1;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("input.txt"));
        int n = in.nextInt();
        A = new int [n];
        for (int i=0;i<n;++i)
            A[i]=in.nextInt();
        dp = new int [n+1];
        PrintWriter out = new PrintWriter(new File("output.txt"));
        out.print(lis(n));
        out.close();
    }
}
