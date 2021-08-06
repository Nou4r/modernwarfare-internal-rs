#![feature(exit_status_error)]

use std::process::Command;

fn main() {
    Command::new("C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin/amd64/MSBuild.exe")
        .args(&["framework/Framework.sln", "/property:Configuration=Release", "/property:Platform=x64"])
        .status()
        .unwrap()
        .exit_ok()
        .expect("Failed to compile Framework.sln");

    println!("cargo:rustc-link-search=native=framework/x64/Release");
    println!("cargo:rustc-link-lib=static=Framework");

    cc::Build::new().file("src/Decryption.cpp").compile("decryption");

    // Include build ID
    let output = Command::new("git").args(&["log", "--pretty=format:%h", "-n", "1"]).output().unwrap();
    let git_hash = String::from_utf8(output.stdout).unwrap().replace("\"", "");

    let output = Command::new("git").args(&["rev-parse", "--abbrev-ref", "HEAD"]).output().unwrap();
    let git_branch = String::from_utf8(output.stdout).unwrap().replace("\"", "");

    let output = Command::new("git").args(&["status", "-s"]).output().unwrap();
    let modified = String::from_utf8(output.stdout).unwrap().contains('M');

    println!("cargo:rustc-env=GIT_BRANCH={}", git_branch);
    println!("cargo:rustc-env=GIT_HASH={}", git_hash);
    println!("cargo:rustc-env=GIT_MODIFIED_STR={}", if modified { " dev" } else { "" });
}