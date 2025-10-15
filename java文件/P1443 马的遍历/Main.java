import java.lang.reflect.Array;
import java.util.*;

public class Main {

    static public class pos{
        public int x;
        public int y;
        public pos(int x, int y){
            this.x = x;
            this.y = y;
        }
    }

    static boolean is_ok(int x, int y){
        if(x<1 || y<1 || x>n || y>m || dis[x][y]!=-1){
            return false;
        }else{
            return true;
        }
    }

    static int n,m,x,y;
    static int[][] dis = new int[405][405];
    static Queue<pos> q = new LinkedList<>();
    static int[] dx = {1,1,-1,-1,2,2,-2,-2};
    static int[] dy = {2,-2,2,-2,1,-1,1,-1};
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        x = sc.nextInt();
        y = sc.nextInt();
        for(int i=0;i<405;i++){
            for(int j=0;j<405;j++){
                dis[i][j] = -1;
            }
        }
        
        q.offer(new pos(x, y));
        dis[x][y] += 1;

        while (!q.isEmpty()){
            pos now = q.poll();
            for(int i=0;i<8;i++){
                pos next = new pos(now.x+dx[i], now.y+dy[i]);
                if(is_ok(next.x,next.y)==true){
                    dis[next.x][next.y] = dis[now.x][now.y]+1;
                    q.offer(next);
                }
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                System.out.printf("%d ",dis[i][j]);
            }
            System.out.println();
        }
    }
}
