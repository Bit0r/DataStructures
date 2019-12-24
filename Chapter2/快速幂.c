double power(long x,long n){
    if(n<0)
        return 1/power(x,-n);
    else if(n==0)
        return 1;
    else if(n%2)
        return power(x,n-1)*x;
    else{
        double t=power(x,n/2);
        return t*t;
    }
}
