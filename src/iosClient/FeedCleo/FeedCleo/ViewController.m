//
//  ViewController.m
//  FeedCleo
//
//  Created by Javier Garrido Díaz on 17/8/18.
//  Copyright © 2018 Javier Garrido Díaz. All rights reserved.
//

#import "ViewController.h"

#define K_URLARDUINO @"http://XXXXXXX"

@interface ViewController ()<NSURLConnectionDelegate, NSURLConnectionDataDelegate>
@property (strong, nonatomic) IBOutlet UIButton *btnFeed;

@end

@implementation ViewController 

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning]; 
  // Dispose of any resources that can be recreated.
}
- (IBAction)feedCleoAction:(id)sender {
  NSURLRequest *request = [[NSURLRequest alloc] initWithURL:[NSURL URLWithString:K_URLARDUINO]];
  NSURLConnection *cnn = [[NSURLConnection alloc] initWithRequest:request delegate:self];
  [cnn start];
}

#pragma mark Errores de la conexión
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error{
  UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Fallo" message:error.domain preferredStyle:UIAlertControllerStyleAlert];
  UIAlertAction *defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
                                                        handler:^(UIAlertAction * action) {}];
  [alert addAction:defaultAction];
  [self presentViewController:alert animated:YES completion:nil];
}

#pragma mark - Captura de Datos de NSURLConnection
- (void)connectionDidFinishLoading:(NSURLConnection *)connection{
  //Fin de la llamada
  UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Alimentando!" message:@"Hecho!" preferredStyle:UIAlertControllerStyleAlert];
  UIAlertAction *defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
                                                        handler:^(UIAlertAction * action) {}];
  [alert addAction:defaultAction];
  [self presentViewController:alert animated:YES completion:nil];
}
@end
