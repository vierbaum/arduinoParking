extern crate sdl2;
use sdl2::pixels::Color;
use sdl2::event::Event;
use sdl2::rect::Rect;
use std::io::{BufRead, BufReader};
use std::fs::File;
use std::any::type_name;

const WINDOWRES :[i32; 2] = [1024, 1024];
pub struct Graphic {
    offset: [i32; 2],
    scale: [i32; 2],
}

impl Graphic {
    pub fn init(&mut self, offset: [i32; 2], scale: [i32; 2]) {
        self.offset = offset;
        self.scale = scale;
    }
    pub fn draw(&mut self, value: i32, pos: i32) {
        //canvas.set_draw_color(Color::RGB(27, 28, 30));
        //canvas.fill_rect(Rect::new(pos + self.offset[0], 0 + self.offset[1], 1, (WINDOWRES[1] - self.offset[1]) as u32));
    }
}

pub fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}


pub fn main() {
    // boring bs
    const arrsize: usize = 512;
    let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();
    let window = video_subsystem.window("sensor", WINDOWRES[0] as u32, WINDOWRES[1] as u32)
        .position_centered()
        .build()
        .unwrap();
    let mut canvas = window.into_canvas().build().unwrap();
    print_type_of(&canvas);
    let mut event_pump = sdl_context.event_pump().unwrap();
    //set background color
    canvas.set_draw_color(Color::RGB(27, 28, 30));
    canvas.clear();
    let mut file = BufReader::new(File::open("/dev/ttyUSB0").expect(""));
    let mut buffer = Vec::<u8>::new();
    let mut posarr = 0;
    let mut values1: [i32; arrsize] = [0; arrsize];
    let mut values2: [i32; arrsize] = [0; arrsize];
    let mut g1: Graphic;


    // actual code
    'running: loop {
        file.read_until(b'\n', &mut buffer).expect("");
        let s = String::from_utf8(buffer).expect("");
        values1[posarr] = s.trim().parse::<i32>().unwrap();
        buffer = s.into_bytes();
        buffer.clear();


        canvas.set_draw_color(Color::RGB(27, 28, 30));
        canvas.fill_rect(Rect::new(posarr as i32, 0, 1, WINDOWRES[1] as u32));
        canvas.set_draw_color(Color::RGB(60, 56, 54));
        canvas.fill_rect(Rect::new(posarr as i32, WINDOWRES[1] - values1[posarr], 1, values1[posarr] as u32));

        posarr = (posarr + 1) % arrsize;

        println!("{}", values1[posarr]);
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit {..}  => {
                    break 'running
                },
                _ => {}
            }
        }
        canvas.present();
    }
}
