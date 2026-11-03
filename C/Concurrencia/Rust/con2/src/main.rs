use std::process::Command;

fn main() {
    let output = Command::new("echo")
        .arg("Hola desde Rust")
        .output()
        .expect("Fallo al ejecutar el proceso");

    if output.status.success() {
        let stdout = String::from_utf8_lossy(&output.stdout);
        println!("Salida del comando: {}", stdout.trim());
    } else {
        let stderr = String::from_utf8_lossy(&output.stderr);
        eprintln!("Error en el comando: {}", stderr);
    }

    let mut child = Command::new("sleep")
        .arg("2")
        .spawn()
        .expect("Fallo al ejecutar el proceso");

    println!("[{}] Proceso hijo esperando 2 segundos", child.id());

    // Esperamos a que finalice el proceso hijo
    let status = child.wait().expect("Error");
    
    println!("Salida del proceso hijo: {}", status);
} 

