//
// Created by Ze Carvalho on 16/04/2022.
//

#include "thirdScenario_.h"

thirdScenario_::thirdScenario_(const vector<request> &requests1, const vector<truck> &trucks1) : abstractAlgorithm(requests1, trucks1) {
    requests = requests1;
    requests = fitsTruck();
    trucks = trucks1;
    if (trucks.size() > 1)
        cout << "---- WARNING : MORE THAN 1 TRUCK PROVIDED ONLY THE FIRST WILL BE CONSIDERED ----" << endl;


}
vector<request> thirdScenario_::fitsTruck() {
    vector<request> deliverable;
    for (int i = 0 ; i < requests.size();i ++){
        if (isDeliverable(i)) deliverable.push_back(requests.at(i));
    }
    return deliverable;
}

bool thirdScenario_::isDeliverable(int i) const {
    auto request = requests.at(i);
    if (express.maxVolume > request.volume && express.maxWeight > request.weight && request.duration + usedTime <= timeFrame) return true;
    return false;
}

void thirdScenario_::compute() {
   cout << knapSack(timeFrame,requests,requests.size());
}

int thirdScenario_::knapSackRec(int W, vector<request> wt, int i,int** dp){
    if (i < 0) //se nao existir 0
        return 0;

    if (dp[i][W] != -1) // se ja tiver calculado devolve o valor calculado
        return dp[i][W];

    if (wt[i].duration + W > timeFrame) { // se a duration mais used time maior que timeframe devole valor anterior
        dp[i][W] = knapSackRec(W, wt,i - 1,dp);
        return dp[i][W];
    }else { // se nao calcula a media do tempo com os pedidos que ja tem?
      //  dp[i][W] = max(val[i]+ knapSackRec(W - wt[i],wt, val,i - 1, dp),knapSackRec(W, wt, val,i - 1, dp)); // funcao antiga para max profit
     //   dp[i][W] = min(average(encomendas + esta , encomendas ate agora...));
    }
        return dp[i][W];
    }


// W = tempo restante
// wt = timeframe de cada um dos requests

// n = size


int thirdScenario_::knapSack(int W,vector<request> wt, int n)
{
	int** dp;
	dp = new int*[n];

	for (int i = 0; i < n; i++)
		dp[i] = new int[W + 1];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < W + 1; j++)
			dp[i][j] = -1;

	return knapSackRec(W, wt,n - 1, dp);
}