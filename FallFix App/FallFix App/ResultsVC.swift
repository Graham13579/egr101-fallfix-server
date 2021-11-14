//
//  ResultsVC.swift
//  FallFix App
//
//  Created by Arya Tschand on 11/1/21.
//

import UIKit

class ResultsVC: UIViewController {

    @IBOutlet weak var graphView: UIImageView!
    @IBOutlet weak var resultsText: UITextView!
    
    var base64String: String = ""
    var resultsString: String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    override func viewDidAppear(_ animated: Bool) {
        getLeader()
    }
    
    func getLeader() {
        printMessagesForUser() {
                (returnval, error) in
                if (returnval)!
                {
                    DispatchQueue.main.async {
                        let newImageData = Data(base64Encoded: self.base64String)
                        
                        if let newImageData = newImageData {
                            self.graphView.image = UIImage(data: newImageData)
                        }
                        self.resultsText.text = self.resultsString
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
            
            let url = NSURL(string: "http://172.28.77.91:5000/retgraph/testsession")
            let request = NSMutableURLRequest(url: url as! URL)
            request.httpMethod = "Get"
            
            request.setValue("application/json; charset=utf-8", forHTTPHeaderField: "Content-Type")
            
            let task = URLSession.shared.dataTask(with: request as URLRequest){ data, response, error in
                if let returned = String(data: data!, encoding: .utf8) {
                    var newret: [String] = returned.components(separatedBy: ",-,")
                    print(newret)
                    self.resultsString = newret[0]
                    self.base64String = newret[1]
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
