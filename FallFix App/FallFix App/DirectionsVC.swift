//
//  DirectionsVC.swift
//  FallFix App
//
//  Created by Arya Tschand on 11/1/21.
//

import UIKit

class DirectionsVC: UIViewController {
    
    var timeleft: Int = 5
    
    @IBOutlet weak var TimeLeftLabel: UILabel!
    
    @IBOutlet weak var Start: UIButton!
        
    @IBOutlet weak var DirectionText: UITextView!
    
    @IBAction func Start(_ sender: Any) {
        self.timer = Timer.scheduledTimer(withTimeInterval: 1, repeats: true, block: { _ in
            self.updateCounting()
        })
    }
    
    var timer = Timer()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        TimeLeftLabel.isHidden = true
        // Do any additional setup after loading the view.
    }
    
    func getLeader() {
        printMessagesForUser() {
                (returnval, error) in
                if (returnval)!
                {
                    DispatchQueue.main.async {
                        let storyboard = UIStoryboard(name: "Main", bundle: nil)
                        let vc = storyboard.instantiateViewController(withIdentifier: "SitStandVC") as UIViewController
                        self.navigationController?.pushViewController(vc, animated: true)
                        
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
            
            let url = NSURL(string: "http://172.28.132.254:5000/getstart/arya125")
            let request = NSMutableURLRequest(url: url as! URL)
            request.httpMethod = "Get"
            
            request.setValue("application/json; charset=utf-8", forHTTPHeaderField: "Content-Type")
            
            let task = URLSession.shared.dataTask(with: request as URLRequest){ data, response, error in
                if let returned = String(data: data!, encoding: .utf8) {
                    var newret: [String] = returned.components(separatedBy: ",")
                    
                    CompletionHandler(true,nil)
                    
                    //self.Severity.text = "hello"
                } else {
                }
                
                //self.Severity.text = "test"
                
            }
            task.resume()
            
            let myurl = NSURL(string: "http://172.28.132.254:5000/sendudp/arya125")
            let myrequest = NSMutableURLRequest(url: myurl as! URL)
            myrequest.httpMethod = "Get"
            
            let mytask = URLSession.shared.dataTask(with: myrequest as URLRequest){ data, response, error in
                if let myreturned = String(data: data!, encoding: .utf8) {
                    var mynewret: [String] = myreturned.components(separatedBy: ",")
                    
                    CompletionHandler(true,nil)
                    
                    //self.Severity.text = "hello"
                } else {
                }
                
                //self.Severity.text = "test"
                
            }
            mytask.resume()
            
        } catch {
            
            print(error)
        }
    }
    
    func updateCounting(){
        if (timeleft > 0) {
            timeleft-=1
            TimeLeftLabel.isHidden = false
            DirectionText.isHidden = true
            TimeLeftLabel.text = "Time Left = " + String(timeleft+1)
        } else {
            timer.invalidate()
            
            getLeader()
            
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
