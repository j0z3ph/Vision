use std::thread;
use std::process;
use std::time;

fn get_proc() {
    println!("{:?}", thread::current().id());
    println!("{}", process::id());
    //println!("{}", gettid::gettid().to_string());
    std::thread::sleep(time::Duration::new(1,0));
}   

fn main() {
    let thread1 = thread::spawn(|| { get_proc(); }); 
    let thread2 = thread::spawn(|| { get_proc(); }); 
    get_proc();
    thread1.join().unwrap();
    thread2.join().unwrap();
}
