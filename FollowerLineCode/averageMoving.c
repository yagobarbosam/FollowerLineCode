

#define N 15 //Media do ultimos Ns numero 

int vals[N];

int moving_avarege(int new_lavue){
    
    int i;
    long int sum = 0;
    
    for(i=N;i>0;i--){
        
        vals[i] = vals[i-1];
        
    }
    
    vals[0] = new_lavue;
    
    for(i= 0; i < N; i++){
        
        sum += vals[i];
    }
    
    return sum/N;
    
}