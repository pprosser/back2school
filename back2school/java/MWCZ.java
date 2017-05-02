import java.util.*;

public class MWCZ {
    int[] degree;     // degree of vertices
    int[] weight;     // weight of vertices
    int[][] A;        // 0/1 adjacency matrix
    int n;            // n vertices
    long nodes;       // number of decisions
    long whenFound;   // node count when incumbent found
    long timeLimit;   // milliseconds
    long cpuTime;     // milliseconds
    long maxWeight;   // weight of max clique
    int style;        // used to flavor algorithm
    int[] solution;   // as it says
    //Vertex[] V;     // for ordering vertices
    boolean trace;    // for a trace
    ArrayList[] P;    // future candidate sets at depth
    Stack<Integer> C; // current/growing clique

    MWCZ (int n,int[][] A,int[] degree,int[] weight,int style) {
	this.n = n;
	this.A = A;
	this.degree = degree;
	this.weight = weight;
	nodes = whenFound = maxWeight = 0;
	cpuTime = timeLimit = -1;
	trace = false;
	this.style = style;
	solution = new int[n];
	P = new ArrayList[n+1];
	C = new Stack<Integer>();
    }

    void search(){
	cpuTime = System.currentTimeMillis();
	nodes = 0;
	for (int i=0;i<=n;i++) P[i] = new ArrayList<Integer>(n-i);
	for (int i=n-1;i>=0;i--) P[0].add(i); // reverse order from colourists
	expand(0,getWeight(C),getWeight(P[0]));
	if (trace) System.out.println(nodes +" "+ maxWeight);
    }

    void expand(int depth,long cWeight,long pWeight){
	//System.out.println(depth +" "+ C +" "+ P[depth]);
	if (timeLimit > 0 && System.currentTimeMillis() - cpuTime >= timeLimit) return;
	nodes++;
	int m = P[depth].size();
	for (int i=m-1;i>=0;i--){
	    if (cWeight + pWeight <= maxWeight) return;
	    int v = (int)P[depth].get(i);
	    C.push(v);
	    P[depth+1].clear();
	    long newPWeight = 0;
	    for (int j=0;j<i;j++){
		int w = (int)P[depth].get(j);
		if (A[v][w] == 1){
		    P[depth+1].add(w); 
		    newPWeight = newPWeight + weight[w];
		}
	    }
	    if (cWeight + weight[v] > maxWeight) saveSolution(C);
	    if (!P[depth+1].isEmpty()) expand(depth+1,cWeight+weight[v],newPWeight);
	    C.pop();
	    pWeight = pWeight - weight[v];
	}
    }

    long getWeight(ArrayList<Integer> v){
	long totalWeight = 0;
	for (int i : v) totalWeight = totalWeight + weight[i];
	return totalWeight;
    }

    long getWeight(Stack<Integer> v){
	long totalWeight = 0;
	for (int i : v) totalWeight = totalWeight + weight[i];
	return totalWeight;
    }

    void saveSolution(Stack<Integer> C){
	Arrays.fill(solution,0);
	for (int i : C) solution[i] = 1;
	maxWeight = getWeight(C);
	whenFound = nodes;
	if (trace) System.out.println(nodes +" "+ maxWeight);
    }
}