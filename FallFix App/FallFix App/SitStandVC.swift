//
//  SitStandVC.swift
//  FallFix App
//
//  Created by Arya Tschand on 11/1/21.
//

import UIKit

class SitStandVC: UIViewController {

    @IBOutlet weak var TimerLabel: UILabel!
    
    @IBOutlet weak var CountLabel: UILabel!
    
    var timeLeft: String = ""
    var count: String = ""
    
    var timer = Timer()

    override func viewDidLoad() {
        self.timer = Timer.scheduledTimer(withTimeInterval: 1, repeats: true, block: { _ in
            self.updateCounting()
        })
    }

    func updateCounting(){
        getLeader()
    }
    
    func getLeader() {
        printMessagesForUser() {
                (returnval, error) in
                if (returnval)!
                {
                    DispatchQueue.main.async {
                        self.TimerLabel.text = self.timeLeft + " Sec"
                        self.CountLabel.text = "Count = " + self.count
                        
                    }
                } else {
                    print(error)
                }
            }
            DispatchQueue.main.async { // Correct
            }
        }
        
    func printMessagesForUser(CompletionHandler: @escaping (Bool?, Error?) -> Void){
        do {
            
            let url = NSURL(string: "http://172.28.194.82:5000/output/arya123/")
            let request = NSMutableURLRequest(url: url as! URL)
            request.httpMethod = "Get"
            
            request.setValue("application/json; charset=utf-8", forHTTPHeaderField: "Content-Type")
            
            let task = URLSession.shared.dataTask(with: request as URLRequest){ data, response, error in
                if let returned = String(data: data!, encoding: .utf8) {
                    var newret: [String] = returned.components(separatedBy: ",")
                    self.timeLeft = newret[0]
                    self.count = newret[1]
                    CompletionHandler(true,nil)
                    
                    //self.Severity.text = "hello"
                } else {
                }
                
                //self.Severity.text = "test"
                
            }
            task.resume()
        } catch {
            
            print(error)
        }
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
