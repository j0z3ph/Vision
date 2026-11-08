use nix::sys::wait::wait;
use nix::unistd::{fork, ForkResult};
use std::process;

fn main() {

    let mut contador = 10; 

    println!("[{}] Proceso padre: {}", process::id(), contador);

    match unsafe { fork() } {
        Ok(ForkResult::Child) => {
            // Proceso hijo
            contador = 67; 
            println!("[{}] Proceso hijo: {}", process::id(), contador);
        }
        Ok(ForkResult::Parent { .. }) => {
            let _ = wait(); // Espera a que el proceso hijo termine
            println!("[{}] Proceso padre: {}", process::id(), contador);
        }
        Err(_) => {
            println!("Error al crear el proceso.");
        }
    }
}
