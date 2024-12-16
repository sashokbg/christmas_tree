$fn = 100;



module stage (a, b, z) {
    h1 = sqrt(a^2 - (a/2)^2);
    h2 = sqrt(b^2 - (b/2)^2);
    
    A2_x = (a - b) / 2;
    A2_y = h1 / 3 - h2 / 3; // Center the top triangle in y
    
    B2_x = A2_x + b;
    B2_y = A2_y;
    
    C2_x = A2_x + b/2;
    C2_y = A2_y + h2;

    polyhedron(
            [
                [0, 0, 0],
                [a/2, h1, 0],
                [a, 0, 0],
                [A2_x, A2_y, z],
                [C2_x, C2_y, z],
                [B2_x, B2_y, z],
            ],
            [
                [2, 1, 0], // bottom
                [3, 4, 5], // top
                [1, 4, 3, 0],
                [2, 5, 4, 1],
                [0, 3, 5, 2],
            ]
    );
}


step_between = 10;
height = 64;

max_val = 3;
initial_base = 260;
initial_top = 140;
h = sqrt(initial_base^2 - (initial_base/2)^2);


for (i = [0:max_val]) {
    current_base = initial_base - initial_base*0.61*i;
    current_top = initial_top - initial_top*0.61*i;
        
    translate([
        (initial_base - current_base) / 2,
        h * 1/3 * i*0.61,
        i*(height + step_between)]){
            stage(current_base, current_top, height);
    }
}

//    h1 = sqrt(base^2 - (base/2)^2);
//    h2 = sqrt(base2^2 - (base2/2)^2);
//
//    h3 = sqrt(base3^2 - (base3/2)^2);
//    h4 = sqrt(base4^2 - (base4/2)^2);

//    translate([(base1 - base2) / 2, (h1 - h2)/3, height + step_between]) 

    
//stage(base1, top1, height);
//
//h1 = sqrt(base1^2 - (base1/2)^2);
//h2 = sqrt(base2^2 - (base2/2)^2);
//
//h3 = sqrt(base3^2 - (base3/2)^2);
//h4 = sqrt(base4^2 - (base4/2)^2);
//
//translate([(base1 - base2) / 2, (h1 - h2)/3, height + step_between]) {
//    stage(base2, top2, height);
//    translate([(base2 - base3) / 2, (h2 - h3) / 3, height + step_between]) {
//        stage(base3, top3, height);
//        translate([(base3 - base4) /2 , (h3 - h4) / 3, height + step_between]) {
//            stage(base4, top4, height);
//        }
//    }
//}









