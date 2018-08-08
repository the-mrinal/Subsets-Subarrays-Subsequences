//dated wed aug 8 3:42 PM (IST)
//in this code following problems solution are there:
// 1.subset return using a 2 dimensional array which is dynamically allocated
//     input: 3
//            1 2 3
//     output:

//             3
//             2
//             2 3
//             1
//             1 3
//             1 2
//             1 2 3
// 2.subset return using a 2 dimensioinal vector
// 3.subset print using a single dimensional array
// 4. subset return which sums up to K
//     input:
//           4
//           2 1 3 2
//           4
//     output:
//           2 2 
//           1 3
// 5.subset print which sums up to K

#include<bits/stdc++.h>
using namespace std;

int subsetReturn(int arr[],int si,int ei,int **out){//using output dynamically allocated 2-D array
    if(si==ei){                                     //base case to check if we traverse all the array
        out[0][0] = 0;                              //put 0 at the 0th row and 0th col as this is the empty subset
        return 1;                                   //and length of empty subset is 0 & return 1 as we 1 subset thats empty!
    }
    int small = subsetReturn(arr,si+1,ei,out);      //call for next element in array and  tell to bring all their subsets
                                                    //with the size as return value
    for(int i=0;i<small;i++){                       //now whatever we get from earlier subset of array we copy it again in output array
                                                    //and add out index element in front to make subsets of this index
        out[i+small][0] = out[i][0] +1;
        out[i+small][1] = arr[si];
        for(int j =1;j<=out[i][0];j++){
            out[i+small][j+1] = out[i][j];
        }
    }
    return 2*small;                                 //lastly as we copied all the subsets hence the size will be twice
}


void subsetReturnV(int *arr,int si,int ei,vector<vector<int>> &out){// here instead of using dynamix array we use vector(STL)

    if(si==ei){                                                     //base case is same as before
        vector<int> p;                                              //but no need of recording the length of each rows
        p.push_back('\0');                                          //as vector maintains it
        out.push_back(p);                                           //hence create a empty vector<int> and push it into 2d out vector
        return;                                                     //represents the empty subarray
    }
    //cout<<"ok";
    subsetReturnV(arr,si+1,ei,out);                                 //call the rest of the array by recursion to fill the subsets
                                                                    //and return 
    int l = out.size();                                             //record the size to copy and append the suurent subsets to the out vector
    for(int i=0;i<l;i++){   
        vector<int> p;    
        p.push_back(arr[si]);
        for(int j=0;j<=out[i].size();j++){
            p.push_back(out[i][j]);
        }
        out.push_back(p);
    }
}

void subsetPrint(int *arr,int si,int ei,int*out){   //printing subsets via single dimensional array
    if(si==ei){                                     //base case same as before
        int i=0;
        while(out[i]!=-1){                          //if base case reached then print all till encounters -1
            cout<<out[i]<<" ";
            i++;
        }
        cout<<endl;
       // out[0] = -1;
        return;
    }
   // cout<<"ok";
    int i=0;
    while(out[i]!=-1){                              //increment the i till we reach the end point of subset array
        i++;
    }
    out[i]=arr[si];                                 //put current element in it
    out[i+1] = -1;                                  
    subsetPrint(arr,si+1,ei,out);                   //call to next elemnt in array
    out[i] = -1;                                    //or another choice dont selece this element and move ahead
    subsetPrint(arr,si+1,ei,out);                   //without this element
}

int subsetSumtoKReturn(int *input,int si,int n,int k ,int out[][50]){ //return all th subsets that sums up to K using 2D statically allocated array
  	if(si==n){                                                        //if we reach to the end of array return with filling smae as in subset return above 
      if(k==0){                                                       //return empty subset with 0 at 0th col & row iff k is 0
        out[0][0] = 0;                                                  
        return 1;
      }else{
        return 0;                                                     //else return 0 as if K is not 0 we dont have our desired subset hence no need recording it
      }
    }
  	int small1[1000][50];                                             //make 2 small 2d arrays to recored the output of smaller arrays
  	int small2[1000][50];
  int size1 = subsetSumtoKReturn(input,si+1,n,k,small1);             //this when we dont select the current element in subset
  int size2 = subsetSumtoKReturn(input,si+1,n,k-input[si],small2);   //when we select the element in the subset
  int row =0;
  for(int i=0;i<size1;i++){                                          //copy the 1st one as it is no changes to output array as this is complete subset that sums up to k
    for(int j=0;j<=small1[i][0];j++){   
      out[row][j] = small1[i][j];
    }
    row++;
  }
   for(int i=0;i<size2;i++){                                        //copy this one after appending the curent element in the array
     out[row][0] = small2[i][0]+1;
     out[row][1] = input[si];
    for(int j=1;j<=small2[i][0];j++){
      out[row][j+1] = small2[i][j];
    }
    row++;
  }
  return row;
  
}

void subsetSumtoKPrint(int *arr ,int si,int ei,int k,int *out){//printing  the subset  sum to k using 1d array
    if(si==ei){                                                //base case same as before
        if(k==0){                                              //only if k is empty that means we got our subset
            int i=0;    
            while(out[i]!=-1){                                  //same expalnation as in subset printing normal
                cout<<out[i++]<<" ";
            }
            cout<<endl;
        }
        return;
    }
    int i=0;
    while(out[i]!=-1){                                         //for explanatoin refer subset printing normal
        i++;
    }
    out[i] = arr[si];
    out[i+1] = -1;
    subsetSumtoKPrint(arr,si+1,ei,k-arr[si],out);
    out[i]  = -1;
    subsetSumtoKPrint(arr,si+1,ei,k,out);
}

int main(){
    int n;
    //input array & its size
    cin>>n;
    int *arr = new int [n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    //subset return

    int p = pow(2,n);
    int **output = new int *[p];
    for(int i=0;i<p;i++){
        output[i] = new int [20];
    }

    int x = subsetReturn(arr,0,n,output);

    for(int i=0;i<x;i++){
        int l = output[i][0];
        for(int j=1;j<=l;j++){
            cout<<output[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<vector<int>> v;
    subsetReturnV(arr,0,n,v);
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            if(v[i][j]==0)
                continue;
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    
    //subsetprint
    int *op = new int[20];
    op[0] = -1;
    subsetPrint(arr,0,n,op);

    //subset sum to k
    //input K
    int k;
    cin>>k;
    int outK[50][50];
    int size = subsetSumtoKReturn(arr,0,n,k,outK);
    for(int i=0;i<size;i++){
        int rsize = outK[i][0];
        for(int j=1;j<=rsize;j++){
            cout<<outK[i][j]<<" ";
        }
        cout<<endl;
    }
    //subset sum to k print one
    int *outP = new int [40];
    outP[0] = -1;
    cout<<"printing"<<endl;
    subsetSumtoKPrint(arr,0,n,k,outP);
}

//@getmrinal