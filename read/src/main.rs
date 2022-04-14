extern crate sdl2;
use sdl2::pixels::Color;
use sdl2::event::Event;
use sdl2::rect::Rect;
use std::io::{BufRead, BufReader};
use std::fs::File;
use std::time::Duration;
use substring::Substring;
const WINDOWRES :[i32; 2] = [1025, 700];
pub struct Graphic {
    pos: u32,
    iOffX: u32,
    iOffY: u32,
    iSizeX: u32,
    iSizeY: u32,
    iScaleX: u32,
    iScaleY: u32,
    iNumberRange: u32,
}

impl Graphic {
    pub fn draw(&mut self, value: i32, canvas: *mut sdl2::render::Canvas<sdl2::video::Window>) {
        // SUPER UNSAFE STUFF, PERCEDE AT OWN RISK!!!
        unsafe {
            // black baground
            (*canvas).set_draw_color(Color::RGB(27, 28, 30));
            // trivial
            (*canvas).fill_rect(Rect::new((self.iOffX + self.iScaleX * self.pos) as i32, (self.iOffY) as i32, self.iScaleX, self.iSizeY));
            // forgore
            (*canvas).set_draw_color(Color::RGB(60, 56, 54));
            // more trivial
            (*canvas).fill_rect(Rect::new((self.iOffX + self.iScaleX * self.pos) as i32, (self.iOffY + (self.iSizeY - value as u32 * self.iScaleY))  as i32, self.iScaleX as u32, self.iScaleY * value as u32));
        }
        self.pos = (self.pos + 1) % self.iNumberRange;
    }
    pub fn setPosition(&mut self, x: u32, y:u32) {
        self.iOffX = x;
        self.iOffY = y;
    }
    pub fn setSize(&mut self, x: u32, y: u32) {
        self.iSizeX = x;
        self.iSizeY = y;
        self.iScaleX = x / self.iNumberRange;
        // yes, its hardcoded, deal with it!
        self.iScaleY = y / 256;
    }
    pub fn new() -> Self {
        Graphic {
            pos: 0,
            iOffX: 0,
            iOffY: 0,
            iSizeX: 0,
            iSizeY: 0,
            iScaleX: 0,
            iScaleY: 0,
            iNumberRange: 256,
        }
    }
}



pub fn main() {
    // boring bs
    let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();
    let window = video_subsystem.window("sensor", WINDOWRES[0] as u32, WINDOWRES[1] as u32).position_centered().build().unwrap();
    let mut canvas = window.into_canvas().build().unwrap();
    let mut event_pump = sdl_context.event_pump().unwrap();

    let mut file = BufReader::new(File::open("/dev/ttyUSB0").expect(""));
    let mut buffer = Vec::<u8>::new();
    let mut g1: Graphic = Graphic::new();
    g1.setPosition(0, 0);
    g1.setSize(512, 256);
    let mut g2: Graphic = Graphic::new();
    g2.setPosition(513, 0);
    g2.setSize(512, 512);
    let mut value1: i32 = 0;


    // actual code
    'running: loop {
        file.read_until(b'\n', &mut buffer).expect("");
        if buffer[0] != 98 && buffer[0] != 97 {
            println!("RECEIVED ILLEGAL BITE: {}", buffer[0]);
            println!("{:?}", buffer);
            buffer.clear();
        } else {
            let s = String::from_utf8(buffer).expect("");
            value1 = s.substring(1, 4).trim().parse::<i32>().unwrap();
            let prefix = s.chars().next().unwrap();
            buffer = s.into_bytes();
            buffer.clear();

            if value1 <= 256 {
                if prefix == 'a' {
                    g1.draw(value1, &mut canvas);
                }
                if prefix == 'b' {
                    g2.draw(value1, &mut canvas);
                }
            } else {
                println!("RECEIVED ILLEGAL VALUE: {}", value1);
            }
        }

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
