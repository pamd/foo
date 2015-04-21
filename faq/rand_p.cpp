/* Facebook question: given a random() function that returns 0 or 1 with probabibily of 
 * 1/2 for either value. Define a random(double p) which should return 0 with probability of
 * p, and return 1 with probability of 1-p.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32113865.html
 */

/*********************************
 * Code by searchlyf
 *********************************/
int RandomOneZero(){
    return rand() % 2;
}
int MyRandom(double p){
    assert (0 <= p && p <= 1);
    if (abs(p - 0.5) < 0.00001)
        return RandomOneZero();
    else if (p > 0.5){
        if (0 == RandomOneZero()){
            return 0;
        } else {
            return MyRandom(2 * (p - 0.5));
        }
    } else {
        if (1 == RandomOneZero()){
            return 1;
        } else {
            return MyRandom(2 * p);
        }
    }
}
void TestMyRandom(){
    for (int i = 0; i < 100; ++i){
        printf("%d\t", MyRandom(0.25));
    }
}

/**********************************
 * Code by swanswan
 **********************************/
int rand2(); // return 0/1

int myrandom(double p) {
if (p<0 || p>1) throw exception();
while (p) {
  p = p*2;
  int bit = floor(p); // 0 or 1
  int r = rand2();
  if (r<bit) return 0;
  if (r>bit) return 1;
  p= p-bit;
}
return 1;
}

/************************************************
 * Code by thrust, based on ideq from newbielisk 
 ************************************************/
int rand_any(double p)
{
  double l=0, r=1;
  while (1) {
    if (l >= p) 
      return 1;
    if (r <= p) 
      return 0;

    double m = (l+r) / 2;
    int x = random();
    if (x) 
      l = m;
    else 
      r = m;
  }
}
