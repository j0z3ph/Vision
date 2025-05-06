use rand::Rng; // 0.8.5
use std::io::{self, Write};
use std::time::Instant;

//const SIZE: u128 = 100_000_000;

fn main() {
    let mut vect: Vec<u128> = Vec::new();
    let mut now = Instant::now();
    let _user_size: u128;
    let mut input_line = String::new();

    print!("Number of tests: ");
    io::stdout().flush().unwrap();
    io::stdin()
        .read_line(&mut input_line)
        .expect("Failed to read line");
    _user_size = input_line.trim().parse().expect("Input not an integer");

    for _ in 0.._user_size {
        vect.push(rand::rng().random_range(0.._user_size));
    }

    let mut elapsed = now.elapsed();
    println!("Elapsed: {elapsed:?}");

    // Busqueda
    println!("Busquedas: ");
    for _ in 0..50 {
        let val = rand::rng().random_range(0.._user_size);
        let mut found = false;
        now = Instant::now();
        for i in &vect {
            if *i == val {
                elapsed = now.elapsed();
                println!("Found ({val}). Elapsed: {elapsed:?}");
                found = true;
                break;
            }
        }
        if !found {
            elapsed = now.elapsed();
            println!("NOT Found. Elapsed: {elapsed:?}");
        }
    }

    //println!("{vect:?}");
}
