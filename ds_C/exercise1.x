struct Exercise1 {
	int n;
	int X<n>;
	int Y<n>;
	double r;
};

program DS_Ex1 { 

        version Ex1_1 {
            int inner_product(Exercise1) = 1;
        } = 1;

        version Ex1_2{
            double mean_value(Exercise1) = 1;
        } = 2;

		version Ex1_3 {
            double product(Exercise1) = 1;
        } = 3;
} = 0x20011001;
