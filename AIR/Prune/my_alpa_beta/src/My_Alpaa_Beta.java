
public class My_Alpaa_Beta {

	static int MIN = -1000;
	static int MAX = 1000;
	
	int minmax(int depth,int nodeIndex,boolean maximizingPlayer,int values[],int h,int alpha,int beta){
		
		if(depth==h)
			return values[nodeIndex];        // IMP::: termonating condition, values[nodeIndex]
		
		if(maximizingPlayer){
			
			int best = MIN;
			
			// note:: i=0;i<2;i++
			for(int i=0;i<2;i++)
			{
				// note:: depth+1
				// note:: nodeIndex*2+i
				int val = minmax(depth+1,nodeIndex*2+i,false,values,h,alpha,beta);
				
				best = Math.max(best, val);
				
				// note:: alpha here
				alpha = Math.max(best, alpha);
				
				if(beta<=alpha)
					break;
			}
			
			return best;
		}
		
		else
		{
			int best = MAX;
			
			for(int i=0;i<2;i++){
				
				int val = minmax(depth+1,nodeIndex*2+i,true,values,h,alpha,beta);
				
				best = Math.min(best, val);
				beta = Math.min(best, beta);
				
				if(beta<=alpha)
					break;
			}
			
			return best;
		}
		
	}
	
	int getHeight(int n){
		
		if(n==1)
			return 0;
		else
			return (1+getHeight(n/2));
	}
	
	
	public static void main(String args[]){
		
		int values[] = {5,6,7,4,5,3,6,6,9,7,5,9,8,6}; // this order
		
		My_Alpaa_Beta ab = new My_Alpaa_Beta();
		
		int height = ab.getHeight(values.length);
		int optimal = ab.minmax(0,0,true,values,height,MIN,MAX); 
		
		System.out.println("Optimal value is :"+optimal);
	}
	
}

