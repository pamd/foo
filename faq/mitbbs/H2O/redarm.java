// mitbbs
// http://www.mitbbs.com/article_t/JobHunting/32331973.html
// Code by redarm

class H2OLock{
    int o = 0;
    int h = 0;

    // Generate hydrogen atom
    public synchronized void callH() throws InterruptedException{
	//if (h < 1 || o < 1){
	if (h < 2 || o < 1) { // dhu fix
	    h++;
	    wait();
	}

	// h >= 2 && o >= 1
	if ( o > 0) {
	    o--;
	    notify();
	}

	System.out.println("H");
    }

    // Generate oxygen atom        
    public synchronized void callO() throws InterruptedException{
	if (h < 2) {
	    o++;
	    wait();
	}

	h = h - 2;
	System.out.println("O");

	notify();
	notify();
    }
}
